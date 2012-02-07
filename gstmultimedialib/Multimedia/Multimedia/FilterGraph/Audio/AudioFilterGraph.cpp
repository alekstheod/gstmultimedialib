/*
 * AudioFilterGraph.cpp
 *
 *  Created on: Jun 6, 2010
 *      Author: m1cro
 */

#include "AudioFilterGraph.h"

namespace multimedia {

AudioFilterGraph::AudioFilterGraph(const std::string& fileName)
		throw (GstException) :
		BasePlaybinFilterGraph(fileName), _sourceFilter(fileName), _audioSink(
				"Audio_Out") {
	if (!setAudioSink(&_audioSink)) {
		throw GstException(
				"AudioFilterGraph::AudioFilterGraph - Set audio sink failed");
	}

	if (!setVideoSink(&_videoOutputFilter)) {
		throw GstException(
				"AudioFilterGraph::AudioFilterGraph - Set video sink failed");
	}
}

AudioFilterGraph::~AudioFilterGraph(void) {
	// TODO Auto-generated destructor stub
}

}
