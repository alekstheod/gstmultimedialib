/*
 * CGLVideoFilterGraph.cpp
 *
 *  Created on: Mar 13, 2011
 *      Author: m1cRo
 */

#include <Multimedia/FilterGraph/Video/CGLVideoFilterGraph.h>

namespace multimedia {

	CGLVideoFilterGraph::CGLVideoFilterGraph(const std::string& filename, const utils::SmartPtr<gl::GLDevice>& glDevice) :
		BasePlaybinFilterGraph(filename), _videoSink(glDevice) {
		if(!this->setVideoSink(&_videoSink)){
			throw GstException("CGLVideoFilterGraph::CGLVideoFilterGraph - setVideoSink failed");
		}

	}

	CGLVideoFilterGraph::~CGLVideoFilterGraph() {
		// TODO Auto-generated destructor stub
	}

}
