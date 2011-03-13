/*
 * VideoFilterGraph.cpp
 *
 *  Created on: Jul 24, 2010
 *      Author: m1cRo
 */

#include <Multimedia/FilterGraph/Video/GLVideoFilterGraph.h>

namespace multimedia {

	GLVideoFilterGraph::GLVideoFilterGraph(const std::string& filename, const utils::SmartPtr<gl::GLDevice>& glDevice) :
		BasePlaybinFilterGraph(filename), _videoSink(glDevice), _audioSink("Audio_Out") {
		if (!SetAudioSink(&_audioSink)) {
			throw GstException("VideoFilterGraph::VideoFilterGraph - Set audio sink failed");
		}

		if (!SetVideoSink(&_videoSink)) {
			throw GstException("VideoFilterGraph::VideoFilterGraph - Set video sink failed");
		}

	}

	GLVideoFilterGraph::~GLVideoFilterGraph() {
		// TODO Auto-generated destructor stub
	}

	bool GLVideoFilterGraph::RegisterGLVideoSinkStrategy(const utils::SmartPtr<CGLVideoSinkFilter::IGLVideoSinkStrategy>& strategy) {
		return _videoSink.RegisterGLVideoSinkStrategy(strategy);
	}

}

