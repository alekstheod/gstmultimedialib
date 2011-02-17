/*
 * BaseConverterFilter.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#include "BaseConverterFilter.h"

namespace multimedia{

	BaseConverterFilter::BaseConverterFilter(const std::string& pluginName, const std::string& description)throw (GstException) {
	    _converter = gst_element_factory_make(pluginName.c_str(), description.c_str());
	    if (_converter == NULL) {
	        throw GstException("BaseConverterFilter::BaseConverterFilter - create converter filter named '" + pluginName + "' failed");
	    }
	}

	bool BaseConverterFilter::Connect(BaseOutputFilter* outputFilter) {
	    if (outputFilter == NULL) {
	        return false;
	    }

	    return gst_element_link(_converter.GetPtr(), outputFilter->_output.GetPtr());
	}

	bool BaseConverterFilter::AddToPipeline(GstElement* pipeline) {
	    if (pipeline == NULL) {
	        return false;
	    }

	    return gst_bin_add(GST_BIN(pipeline), _converter.GetPtr());
	}

	BaseConverterFilter::~BaseConverterFilter(void) {

	}

}

