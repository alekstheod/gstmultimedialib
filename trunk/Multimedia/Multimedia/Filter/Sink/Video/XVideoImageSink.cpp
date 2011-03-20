/*
 * XVideoImageSink.cpp
 *
 *  Created on: Feb 23, 2011
 *      Author: m1cRo
 */

#include "XVideoImageSink.h"
#include <gst/interfaces/xoverlay.h>

namespace multimedia {

	const std::string XVideoImageSink::CONST_PLUGIN_NAME="xvimagesink";

	XVideoImageSink::XVideoImageSink(const std::string& description)throw(GstException) : BaseSinkFilter(CONST_PLUGIN_NAME, description) {
		// TODO Auto-generated constructor stub
	}


	XVideoImageSink::XVideoImageSink(const std::string& description, gulong xWindowId)throw(GstException): BaseSinkFilter(CONST_PLUGIN_NAME, description){
		GstXOverlay* gstXOverlay=GST_X_OVERLAY( _output.getPtr());
		gst_x_overlay_set_xwindow_id(gstXOverlay, xWindowId);
	}


	XVideoImageSink::~XVideoImageSink() {
		// TODO Auto-generated destructor stub
	}

}
