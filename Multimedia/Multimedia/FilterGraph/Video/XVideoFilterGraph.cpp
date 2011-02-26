/*
 * XVideoFilterGraph.cpp
 *
 *  Created on: Feb 23, 2011
 *      Author: m1cRo
 */

#include "XVideoFilterGraph.h"

namespace multimedia {

	XVideoFilterGraph::XVideoFilterGraph(const std::string& fileName)throw(GstException) :
		BasePlaybinFilterGraph(fileName), _videoSink("VideoSink"), _audioSink("AudioSink") {
		if (!SetAudioSink(&_audioSink)) {
			throw GstException("XImageVideoFilterGraph::XImageVideoFilterGraph- Set audio sink failed");
		}

		if (!SetVideoSink(&_videoSink)) {
			throw GstException("XImageVideoFilterGraph::XImageVideoFilterGraph - Set video sink failed");
		}
	}


	XVideoFilterGraph::XVideoFilterGraph(const std::string& fileName, gulong xWindowId)throw(GstException):
		BasePlaybinFilterGraph(fileName), _videoSink("VideoSink", xWindowId), _audioSink("AudioSink") {
		if (!SetAudioSink(&_audioSink)) {
			throw GstException("XImageVideoFilterGraph::XImageVideoFilterGraph- Set audio sink failed");
		}

		if (!SetVideoSink(&_videoSink)) {
			throw GstException("XImageVideoFilterGraph::XImageVideoFilterGraph - Set video sink failed");
		}
	}


	XVideoFilterGraph::~XVideoFilterGraph() {
		// TODO Auto-generated destructor stub
	}

}
