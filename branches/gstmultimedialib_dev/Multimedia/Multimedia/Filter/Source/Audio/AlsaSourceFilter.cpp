/*
 * AlsaSourceFilter.cpp
 *
 *  Created on: Jul 11, 2010
 *      Author: m1cRo
 */

#include <Multimedia/Filter/Source/Audio/AlsaSourceFilter.h>

namespace multimedia {

const std::string AlsaSourceFilter::CONST_PLUGIN_NAME = "alsasrc";

AlsaSourceFilter::AlsaSourceFilter(const std::string& pluginDescription) {
	_alsaSource = gst_element_factory_make(CONST_PLUGIN_NAME.c_str(),
			pluginDescription.c_str());
	if (_alsaSource == NULL) {
		throw GstException(
				"AlsaSourceFilter::AlsaSourceFilter - create output filter named '"
						+ CONST_PLUGIN_NAME + "' failed");
	}
}

AlsaSourceFilter::~AlsaSourceFilter(void) {
	// TODO Auto-generated destructor stub
}

}

