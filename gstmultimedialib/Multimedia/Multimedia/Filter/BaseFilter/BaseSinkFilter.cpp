/*
 * BaseOutputFilter.cpp
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#include <Multimedia/Filter/BaseFilter/BaseSinkFilter.h>

namespace multimedia {

BaseSinkFilter::BaseSinkFilter(const std::string& pluginName,
		const std::string& description){
	_output = gst_element_factory_make(pluginName.c_str(), description.c_str());
	if (_output == NULL) {
		throw GstException(
				"BaseOutputFilter::BaseOutputFilter - create output filter named '"
						+ pluginName + "' failed");
	}
}

bool BaseSinkFilter::addToPipeline(GstElement* pipeline) {
	if (pipeline == NULL) {
		return false;
	}

	return gst_bin_add(GST_BIN(pipeline), _output.getPtr());
}

BaseSinkFilter::~BaseSinkFilter(void) {

}

}

