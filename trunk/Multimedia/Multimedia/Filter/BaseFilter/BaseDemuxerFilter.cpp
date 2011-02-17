/*
 * ADemuxer.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#include "BaseDemuxerFilter.h"
#include "BaseDecoderFilter.h"

namespace multimedia {

	BaseDemuxerFilter::BaseDemuxerFilter(const std::string& pluginName, const std::string& description) throw (GstException) {
		_demuxer = gst_element_factory_make(pluginName.c_str(), description.c_str());
		if (_demuxer == NULL) {
			throw GstException("BaseDemuxerFilter::BaseDemuxerFilter - create demuxer filter named '" + pluginName + "' failed");
		}

		_videoDecoder = NULL;
		_audioDecoder = NULL;
	}

	bool BaseDemuxerFilter::Connect(BaseDecoderFilter* decoder) {
		if (decoder == NULL) {
			return false;
		}

		return gst_element_link(_demuxer.GetPtr(), decoder->_decoder.GetPtr());
	}

	bool BaseDemuxerFilter::DynamicConnectVideo(BaseDecoderFilter* videoDecoder) {
		if (_videoDecoder == NULL && _audioDecoder == NULL) {
			g_signal_connect(_demuxer.GetPtr(), "pad-added", G_CALLBACK(OnAddPad), NULL);
		}

		_videoDecoder = videoDecoder->_decoder;
		return true;
	}

	bool BaseDemuxerFilter::DynamicConnectAudio(BaseDecoderFilter* audioDecoder) {
		if (_videoDecoder == NULL && _audioDecoder == NULL) {
			g_signal_connect(_demuxer.GetPtr(), "pad-added", G_CALLBACK(OnAddPad), this);
		}

		_audioDecoder = audioDecoder->_decoder;
		return true;
	}

	bool BaseDemuxerFilter::AddToPipeline(GstElement* pipeline) {
		if (pipeline == NULL) {
			return false;
		}

		return gst_bin_add(GST_BIN(pipeline), _demuxer.GetPtr());
	}

	void BaseDemuxerFilter::OnAddPad(GstElement* element, GstPad* pad, gpointer data) {
		if (data != NULL) {
			BaseDemuxerFilter* _this = (BaseDemuxerFilter*) data;
			_this->NewPad(element, pad);
		}
	}

	void BaseDemuxerFilter::NewPad(GstElement* element, GstPad* pad) {
		if (_audioDecoder != NULL && pad != NULL && element != NULL) {
			GstPad *sinkPad = gst_element_get_static_pad(_audioDecoder.GetPtr(), "sink");
			if (gst_pad_is_linked(pad) == false && gst_pad_is_linked(sinkPad) == false && gst_pad_can_link(pad, sinkPad)) {
				gst_pad_link(pad, sinkPad);
			}
			gst_object_unref(sinkPad);
		}

		if (_videoDecoder != NULL && pad != NULL && element != NULL) {
			GstPad *sinkPad = gst_element_get_static_pad(_videoDecoder.GetPtr(), "sink");
			if (gst_pad_is_linked(pad) == false && gst_pad_is_linked(sinkPad) == false && gst_pad_can_link(pad, sinkPad)) {
				gst_pad_link(pad, sinkPad);
			}
			gst_object_unref(sinkPad);
		}
	}

	BaseDemuxerFilter::~BaseDemuxerFilter(void) {

	}

}

