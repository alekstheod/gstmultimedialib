/*
 * XVideoImageSink.cpp
 *
 *  Created on: Feb 23, 2011
 *      Author: m1cRo
 */

#include "XVideoImageSink.h"

namespace multimedia {

	const std::string XVideoImageSink::CONST_PLUGIN_NAME="xvimagesink";

	XVideoImageSink::XVideoImageSink(const std::string& description)throw(GstException) : BaseSinkFilter(CONST_PLUGIN_NAME, description) {
		// TODO Auto-generated constructor stub

	}

	XVideoImageSink::~XVideoImageSink() {
		// TODO Auto-generated destructor stub
	}

}
