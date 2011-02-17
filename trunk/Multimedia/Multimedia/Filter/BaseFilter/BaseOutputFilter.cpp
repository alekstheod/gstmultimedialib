/*
 * BaseOutputFilter.cpp
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#include "BaseOutputFilter.h"

namespace multimedia {

	BaseOutputFilter::BaseOutputFilter(const std::string& pluginName, const std::string& description) throw (GstException) {
		_output = gst_element_factory_make(pluginName.c_str(), description.c_str());
		if (_output == NULL) {
			throw GstException("BaseOutputFilter::BaseOutputFilter - create output filter named '" + pluginName + "' failed");
		}
	}

	bool BaseOutputFilter::AddToPipeline(GstElement* pipeline) {
		if (pipeline == NULL) {
			return false;
		}

		return gst_bin_add(GST_BIN(pipeline), _output.GetPtr());
	}

	BaseOutputFilter::~BaseOutputFilter(void) {

	}

}

