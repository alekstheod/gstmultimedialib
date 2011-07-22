/*
 * GstObject.cpp
 *
 *  Created on: Jul 22, 2011
 *      Author: alekstheod
 */

#include "GstObject.h"
#include <gst/gst.h>

namespace multimedia {

	const bool GstObject::CONST_GST_INITIALIZED=initGstreamer();

	GstObject::GstObject() {
		// TODO Auto-generated constructor stub
	}


	bool GstObject::initGstreamer(){
		gst_init(NULL, NULL);
		return true;
	}


	GstObject::~GstObject() {
		// TODO Auto-generated destructor stub
	}

}
