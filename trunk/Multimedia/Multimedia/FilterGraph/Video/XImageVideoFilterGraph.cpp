/*
 * XImageVideoFilterGraph.cpp
 *
 *  Created on: Feb 23, 2011
 *      Author: m1cRo
 */

#include <Multimedia/FilterGraph/Video/XImageVideoFilterGraph.h>

namespace multimedia {

	XImageVideoFilterGraph::XImageVideoFilterGraph(const std::string& fileName) : BasePlaybinFilterGraph(fileName), _videoSink("VideoSink"), _audioSink("AudioSink") {
		if (!SetAudioSink(&_audioSink)) {
			throw GstException("XImageVideoFilterGraph::XImageVideoFilterGraph- Set audio sink failed");
		}

		if (!SetVideoSink(&_videoSink)) {
			throw GstException("XImageVideoFilterGraph::XImageVideoFilterGraph - Set video sink failed");
		}
	}


	XImageVideoFilterGraph::~XImageVideoFilterGraph() {
		// TODO Auto-generated destructor stub
	}

}
