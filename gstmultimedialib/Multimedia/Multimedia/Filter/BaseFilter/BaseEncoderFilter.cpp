/*
 * BaseEncoderFilter.cpp
 *
 *  Created on: Jul 10, 2010
 *      Author: m1cRo
 */

#include "BaseEncoderFilter.h"

namespace multimedia {

BaseEncoderFilter::BaseEncoderFilter(const std::string& pluginName,
		const std::string& description) throw (GstException) {
	_encoder = gst_element_factory_make(pluginName.c_str(),
			description.c_str());
	if (_encoder == NULL) {
		throw GstException(
				"BaseDecoderFilter::BaseDecoderFilter - create encoder filter named '"
						+ pluginName + "' failed");
	}
}

bool BaseEncoderFilter::addToPipeline(GstElement* pipeline) {
	if (pipeline == NULL) {
		return false;
	}

	return gst_bin_add(GST_BIN(pipeline), _encoder.getPtr());
}

BaseEncoderFilter::~BaseEncoderFilter() {
	// TODO Auto-generated destructor stub
}

}
