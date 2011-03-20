/*
 * SampleGrabberSinkFilter.cpp
 *
 *  Created on: Mar 19, 2011
 *      Author: m1cRo
 */

#include "SampleGrabberSinkFilter.h"

namespace multimedia {

	SampleGrabberSinkFilter::SampleGrabberSinkFilter(const std::string& description):ABaseCallbackSinkFilter(description) {
		// TODO Auto-generated constructor stub

	}

	SampleGrabberSinkFilter::~SampleGrabberSinkFilter() {
		// TODO Auto-generated destructor stub
	}


	bool SampleGrabberSinkFilter::onRecieveBuffer(GstPad* gstPad, GstBuffer* gstBuffer){
		return true;
	}


	bool SampleGrabberSinkFilter::onSetCaps(GstPad * pad, GstCaps * caps){
		return true;
	}

}
