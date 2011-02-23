/*
 * BaseDecoderFilter.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#include "BaseDecoderFilter.h"

namespace multimedia {

	BaseDecoderFilter::BaseDecoderFilter(const std::string& pluginName, const std::string& description) throw (GstException) {
		_decoder = gst_element_factory_make(pluginName.c_str(), description.c_str());
		if (_decoder == NULL) {
			throw GstException("BaseDecoderFilter::BaseDecoderFilter - create decoder filter named '" + pluginName + "' failed");
		}
	}

	bool BaseDecoderFilter::Connect(BaseConverterFilter* converter) {
		if (converter == NULL) {
			return false;
		}

		return gst_element_link(_decoder.GetPtr(), converter->_converter.GetPtr());
	}

	bool BaseDecoderFilter::Connect(BaseSinkFilter* outputFilter) {
		if (outputFilter == NULL) {
			return false;
		}

		return gst_element_link(_decoder.GetPtr(), outputFilter->_output.GetPtr());
	}

	bool BaseDecoderFilter::Connect(BaseEncoderFilter* encoderFilter) {
		if (encoderFilter == NULL) {
			return false;
		}

		return gst_element_link(_decoder.GetPtr(), encoderFilter->_encoder.GetPtr());
	}

	bool BaseDecoderFilter::AddToPipeline(GstElement* pipeline) {
		if (pipeline == NULL) {
			return false;
		}

		return gst_bin_add(GST_BIN(pipeline), _decoder.GetPtr());
	}

	BaseDecoderFilter::~BaseDecoderFilter(void) {

	}

}

