/*
 * BaseDecoderFilter.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#include "BaseDecoderFilter.h"

namespace multimedia {

BaseDecoderFilter::BaseDecoderFilter(const std::string& pluginName,
		const std::string& description) throw (GstException) {
	m_decoder = gst_element_factory_make(pluginName.c_str(),
			description.c_str());
	if (m_decoder == NULL) {
		throw GstException(
				"BaseDecoderFilter::BaseDecoderFilter - create decoder filter named '"
						+ pluginName + "' failed");
	}
}

bool BaseDecoderFilter::connect(BaseConverterFilter* converter) {
	if (converter == NULL) {
		return false;
	}

	return gst_element_link(m_decoder.getPtr(), converter->m_converter.getPtr());
}

bool BaseDecoderFilter::connect(BaseSinkFilter* outputFilter) {
	if (outputFilter == NULL) {
		return false;
	}

	return gst_element_link(m_decoder.getPtr(), outputFilter->m_output.getPtr());
}

bool BaseDecoderFilter::connect(BaseEncoderFilter* encoderFilter) {
	if (encoderFilter == NULL) {
		return false;
	}

	return gst_element_link(m_decoder.getPtr(), encoderFilter->m_encoder.getPtr());
}

bool BaseDecoderFilter::addToPipeline(GstElement* pipeline) {
	if (pipeline == NULL) {
		return false;
	}

	return gst_bin_add(GST_BIN(pipeline), m_decoder.getPtr());
}

BaseDecoderFilter::~BaseDecoderFilter(void) {

}

}

