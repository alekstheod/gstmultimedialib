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
		const std::string& description) throw (GstException) {
	_demuxer = gst_element_factory_make(pluginName.c_str(),
			description.c_str());
	if (_demuxer == NULL) {
		throw GstException(
				"BaseDemuxerFilter::BaseDemuxerFilter - create demuxer filter named '"
						+ pluginName + "' failed");
	}

	_videoDecoder = NULL;
	_audioDecoder = NULL;
}

bool BaseDemuxerFilter::connect(BaseDecoderFilter* decoder) {
	if (decoder == NULL) {
		return false;
	}

	return gst_element_link(_demuxer.getPtr(), decoder->_decoder.getPtr());
}

bool BaseDemuxerFilter::dynamicConnectVideo(BaseDecoderFilter* videoDecoder) {
	if (_videoDecoder == NULL && _audioDecoder == NULL) {
		g_signal_connect(_demuxer.getPtr(), "pad-added", G_CALLBACK(onAddPad),
				NULL);
	}

	_videoDecoder = videoDecoder->_decoder;
	return true;
}

bool BaseDemuxerFilter::dynamicConnectAudio(BaseDecoderFilter* audioDecoder) {
	if (_videoDecoder == NULL && _audioDecoder == NULL) {
		g_signal_connect(_demuxer.getPtr(), "pad-added", G_CALLBACK(onAddPad),
				this);
	}

	_audioDecoder = audioDecoder->_decoder;
	return true;
}

bool BaseDemuxerFilter::addToPipeline(GstElement* pipeline) {
	if (pipeline == NULL) {
		return false;
	}

	return gst_bin_add(GST_BIN(pipeline), _demuxer.getPtr());
}

void BaseDemuxerFilter::onAddPad(GstElement* element, GstPad* pad,
		gpointer data) {
	if (data != NULL) {
		BaseDemuxerFilter* _this = (BaseDemuxerFilter*) data;
		_this->newPad(element, pad);
	}
}

void BaseDemuxerFilter::newPad(GstElement* element, GstPad* pad) {
	if (_audioDecoder != NULL && pad != NULL && element != NULL) {
		GstPad *sinkPad = gst_element_get_static_pad(_audioDecoder.getPtr(),
				"sink");
		if (gst_pad_is_linked(pad) == false
				&& gst_pad_is_linked(sinkPad) == false
				&& gst_pad_can_link(pad, sinkPad)) {
			gst_pad_link(pad, sinkPad);
		}
		gst_object_unref(sinkPad);
	}

	if (_videoDecoder != NULL && pad != NULL && element != NULL) {
		GstPad *sinkPad = gst_element_get_static_pad(_videoDecoder.getPtr(),
				"sink");
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

