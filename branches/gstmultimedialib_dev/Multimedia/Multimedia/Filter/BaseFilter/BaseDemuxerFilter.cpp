/*
 * ADemuxer.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#include "BaseDemuxerFilter.h"
#include "BaseDecoderFilter.h"

namespace multimedia {

BaseDemuxerFilter::BaseDemuxerFilter(const std::string& pluginName,
                                     const std::string& description) : m_demuxer( gst_element_factory_make(pluginName.c_str(), description.c_str()) ) {
        if (m_demuxer == NULL) {
            throw GstException(
                "BaseDemuxerFilter::BaseDemuxerFilter - create demuxer filter named '"
                + pluginName + "' failed");
        }

        m_videoDecoder = NULL;
        m_audioDecoder = NULL;
    }

    bool BaseDemuxerFilter::connect(BaseDecoderFilter* decoder) {
        if (decoder == NULL) {
            return false;
        }

        return gst_element_link(m_demuxer.getPtr(), decoder->m_decoder.getPtr());
    }

    bool BaseDemuxerFilter::dynamicConnectVideo(BaseDecoderFilter* videoDecoder) {
        if (m_videoDecoder == NULL && m_audioDecoder == NULL) {
            g_signal_connect(m_demuxer.getPtr(), "pad-added", G_CALLBACK(onAddPad), NULL);
        }

        m_videoDecoder = videoDecoder->m_decoder;
        return true;
    }

    bool BaseDemuxerFilter::dynamicConnectAudio(BaseDecoderFilter* audioDecoder) {
        if (m_videoDecoder == NULL && m_audioDecoder == NULL) {
            g_signal_connect(m_demuxer.getPtr(), "pad-added", G_CALLBACK(onAddPad), this);
        }

        m_audioDecoder = audioDecoder->m_decoder;
        return true;
    }

    bool BaseDemuxerFilter::addToPipelineImpl(GstElement* pipeline) {
        if (pipeline == NULL) {
            return false;
        }

        return gst_bin_add(GST_BIN(pipeline), m_demuxer.getPtr());
    }

    void BaseDemuxerFilter::onAddPad(GstElement* element, GstPad* pad,
    gpointer data) {
        if (data != NULL) {
            BaseDemuxerFilter* _this = (BaseDemuxerFilter*) data;
            _this->newPad(element, pad);
        }
    }

    void BaseDemuxerFilter::newPad(GstElement* element, GstPad* pad) {
        if (m_audioDecoder != NULL && pad != NULL && element != NULL) {
            GstPad *sinkPad = gst_element_get_static_pad(m_audioDecoder.getPtr(), "sink");
            if (gst_pad_is_linked(pad) == false
                    && gst_pad_is_linked(sinkPad) == false
            && gst_pad_can_link(pad, sinkPad)) {
                gst_pad_link(pad, sinkPad);
            }
            gst_object_unref(sinkPad);
        }

        if (m_videoDecoder != NULL && pad != NULL && element != NULL) {
            GstPad *sinkPad = gst_element_get_static_pad(m_videoDecoder.getPtr(), "sink");
            if (gst_pad_is_linked(pad) == false
                    && gst_pad_is_linked(sinkPad) == false
            && gst_pad_can_link(pad, sinkPad)) {
                gst_pad_link(pad, sinkPad);
            }
            gst_object_unref(sinkPad);
        }
    }

    BaseDemuxerFilter::~BaseDemuxerFilter(void) {

    }

}

