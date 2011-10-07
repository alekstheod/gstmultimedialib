/*
 * ImageVideoSink.cpp
 *
 *  Created on: Feb 23, 2011
 *      Author: m1cRo
 */

#include <Multimedia/Filter/Sink/Video/XImageVideoSinkFilter.h>

namespace multimedia {

const std::string XImageVideoSinkFilter::CONST_PLUGIN_NAME = "ximagesink";

XImageVideoSinkFilter::XImageVideoSinkFilter(const std::string& description) :
		BaseSinkFilter(CONST_PLUGIN_NAME, description) {
	// TODO Auto-generated constructor stub
}

XImageVideoSinkFilter::~XImageVideoSinkFilter() {
	// TODO Auto-generated destructor stub
}

}
