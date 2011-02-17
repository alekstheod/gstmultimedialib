/*
 * VideoFilterGraph.cpp
 *
 *  Created on: Jul 24, 2010
 *      Author: m1cRo
 */

#include <Multimedia/FilterGraph/Video/VideoFilterGraph.h>

namespace multimedia {

	VideoFilterGraph::VideoFilterGraph(const std::string& filename, const utils::SmartPtr<gl::GLDevice>& glDevice) :
		BasePlaybinFilterGraph(filename), _videoSink(glDevice) {
		if (!SetAudioSink(&_audioSink)) {
			throw GstException("VideoFilterGraph::VideoFilterGraph - Set audio sink failed");
		}

		if (!SetVideoSink(&_videoSink)) {
			throw GstException("VideoFilterGraph::VideoFilterGraph - Set video sink failed");
		}

	}

	VideoFilterGraph::~VideoFilterGraph() {
		// TODO Auto-generated destructor stub
	}

	bool VideoFilterGraph::RegisterGLVideoSinkStrategy(const utils::SmartPtr<GLVideoSink::IGLVideoSinkStrategy>& strategy) {
		return _videoSink.RegisterGLVideoSinkStrategy(strategy);
	}

}

