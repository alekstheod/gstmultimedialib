/*
 * Mp3FilterGraph.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#include <Multimedia/FilterGraph/Audio/Mp3FilterGraph.h>

namespace multimedia{

	Mp3FilterGraph::Mp3FilterGraph(const std::string& sourceFileName)throw (GstException) : BaseFilterGraph("Mp3Player"), _src(sourceFileName), _audioOutput("Audio_Out") {
	    if (!AddFilter(&_src)) {
	        throw GstException("Mp3FilterGraph::Mp3FilterGraph - Create pipeline failed");
	    }

	    if (!AddFilter(&_demuxer)) {
	        throw GstException("Mp3FilterGraph::Mp3FilterGraph - Create pipeline failed");
	    }

	    if (!AddFilter(&_decoder)) {
	        throw GstException("Mp3FilterGraph::Mp3FilterGraph - Create pipeline failed");
	    }

	    if (!AddFilter(&_converter)) {
	        throw GstException("Mp3FilterGraph::Mp3FilterGraph - Create pipeline failed");
	    }

	    if (!AddFilter(&_audioOutput)) {
	        throw GstException("Mp3FilterGraph::Mp3FilterGraph - Create pipeline failed");
	    }

	    if (!_src.Connect(&_demuxer)) {
	        throw GstException("Mp3FilterGraph::Mp3FilterGraph - Source->Demuxer failed");
	    }

	    if (!_decoder.Connect(&_converter)) {
	        throw GstException("Mp3FilterGraph::Mp3FilterGraph - Decoder->Converter failed");
	    }

	    if (!_converter.Connect(&_audioOutput)) {
	        throw GstException("Mp3FilterGraph::Mp3FilterGraph - Converter->Output failed");
	    }

	    if (!_demuxer.DynamicConnectAudio(&_decoder)) {
	        throw GstException("Mp3FilterGraph::Mp3FilterGraph - Demuxer->Decoder failed");
	    }
	}

	Mp3FilterGraph::~Mp3FilterGraph(void) {
	}

}

