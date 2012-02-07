/*
 * VideoFilterGraph.cpp
 *
 *  Created on: Jul 24, 2010
 *      Author: m1cRo
 */

#include <Multimedia/FilterGraph/Video/GLVideoFilterGraph.h>

namespace multimedia {

GLVideoFilterGraph::GLVideoFilterGraph(const std::string& filename,
		const utils::SmartPtr<gl::Device>& glDevice) :
		BasePlaybinFilterGraph(filename), _videoSink(glDevice), _audioSink(
				"Audio_Out") {
	if (!setAudioSink(&_audioSink)) {
		throw GstException(
				"VideoFilterGraph::VideoFilterGraph - Set audio sink failed");
	}

	if (!setVideoSink(&_videoSink)) {
		throw GstException(
				"VideoFilterGraph::VideoFilterGraph - Set video sink failed");
	}

}

GLVideoFilterGraph::~GLVideoFilterGraph() {
	// TODO Auto-generated destructor stub
}
}

