/*
 * Mp3FilterGraph.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#include <Multimedia/FilterGraph/Audio/Mp3FilterGraph.h>

namespace multimedia {

Mp3FilterGraph::Mp3FilterGraph(const std::string& sourceFileName)
		throw (GstException) :
		BaseFilterGraph("Mp3Player"), _src(sourceFileName), _audioOutput(
				"Audio_Out") {
	if (!addFilter(&_src)) {
		throw GstException(
				"Mp3FilterGraph::Mp3FilterGraph - Create pipeline failed");
	}

	if (!addFilter(&_demuxer)) {
		throw GstException(
				"Mp3FilterGraph::Mp3FilterGraph - Create pipeline failed");
	}

	if (!addFilter(&_decoder)) {
		throw GstException(
				"Mp3FilterGraph::Mp3FilterGraph - Create pipeline failed");
	}

	if (!addFilter(&_converter)) {
		throw GstException(
				"Mp3FilterGraph::Mp3FilterGraph - Create pipeline failed");
	}

	if (!addFilter(&_audioOutput)) {
		throw GstException(
				"Mp3FilterGraph::Mp3FilterGraph - Create pipeline failed");
	}

	if (!_src.Connect(&_demuxer)) {
		throw GstException(
				"Mp3FilterGraph::Mp3FilterGraph - Source->Demuxer failed");
	}

	if (!_decoder.connect(&_converter)) {
		throw GstException(
				"Mp3FilterGraph::Mp3FilterGraph - Decoder->Converter failed");
	}

	if (!_converter.connect(&_audioOutput)) {
		throw GstException(
				"Mp3FilterGraph::Mp3FilterGraph - Converter->Output failed");
	}

	if (!_demuxer.dynamicConnectAudio(&_decoder)) {
		throw GstException(
				"Mp3FilterGraph::Mp3FilterGraph - Demuxer->Decoder failed");
	}
}

Mp3FilterGraph::~Mp3FilterGraph(void) {
}

}

