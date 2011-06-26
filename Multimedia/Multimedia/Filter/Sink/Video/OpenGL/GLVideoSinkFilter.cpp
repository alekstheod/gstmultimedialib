/*
 * GLVideoSink.cpp
 *
 *  Created on: Feb 22, 2011
 *      Author: m1cRo
 */

#include <Multimedia/Filter/Sink/Video/OpenGL/GLVideoSinkFilter.h>

namespace multimedia {

	const std::string GLVideoSinkFilter::CONST_PLUGIN_NAME="glimagesink";

	GLVideoSinkFilter::GLVideoSinkFilter(const std::string& description) : BaseSinkFilter(CONST_PLUGIN_NAME, description) {
		// TODO Auto-generated constructor stub

	}

	GLVideoSinkFilter::~GLVideoSinkFilter() {
		// TODO Auto-generated destructor stub
	}

}
