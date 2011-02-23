/*
 * XImageVideoFilterGraph.cpp
 *
 *  Created on: Feb 23, 2011
 *      Author: m1cRo
 */

#include <Multimedia/FilterGraph/Video/XImageVideoFilterGraph.h>

namespace multimedia {

	XImageVideoFilterGraph::XImageVideoFilterGraph(const std::string& fileName) : BasePlaybinFilterGraph(fileName), _videoSink("VideoSink"), _audioSink("AudioSink") {
		// TODO Auto-generated constructor stub

	}

	XImageVideoFilterGraph::~XImageVideoFilterGraph() {
		// TODO Auto-generated destructor stub
	}

}
