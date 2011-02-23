/*
 * ImageVideoSink.cpp
 *
 *  Created on: Feb 23, 2011
 *      Author: m1cRo
 */

#include "ImageVideoSink.h"

namespace multimedia {

	const std::string ImageVideoSink::CONST_PLUGIN_NAME="ximagesink";

	ImageVideoSink::ImageVideoSink(const std::string& description):BaseSinkFilter(CONST_PLUGIN_NAME,description) {
		// TODO Auto-generated constructor stub
	}


	ImageVideoSink::~ImageVideoSink() {
		// TODO Auto-generated destructor stub
	}

}
