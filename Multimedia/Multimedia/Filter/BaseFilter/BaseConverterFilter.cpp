/*
 * BaseConverterFilter.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#include "BaseConverterFilter.h"

namespace multimedia {

BaseConverterFilter::BaseConverterFilter(const std::string& pluginName,
		const std::string& description) throw (GstException) {
	_converter = gst_element_factory_make(pluginName.c_str(),
			description.c_str());
	if (_converter == NULL) {
		throw GstException(
				"BaseConverterFilter::BaseConverterFilter - create converter filter named '"
						+ pluginName + "' failed");
	}
}

bool BaseConverterFilter::connect(BaseSinkFilter* outputFilter) {
	if (outputFilter == NULL) {
		return false;
	}

	return gst_element_link(_converter.getPtr(), outputFilter->_output.getPtr());
}

bool BaseConverterFilter::addToPipeline(GstElement* pipeline) {
	if (pipeline == NULL) {
		return false;
	}

	return gst_bin_add(GST_BIN(pipeline), _converter.getPtr());
}

BaseConverterFilter::~BaseConverterFilter(void) {

}

}

