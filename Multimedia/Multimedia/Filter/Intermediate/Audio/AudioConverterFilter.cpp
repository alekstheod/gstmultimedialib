/*
 * AudioConverterFilter.cpp
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#include <Multimedia/Filter/Intermediate/Audio/AudioConverterFilter.h>

namespace multimedia {

const std::string AudioConverterFilter::CONST_PLUGIN_NAME = "audioconvert";
const std::string AudioConverterFilter::CONST_PLUGIN_DESCRIPTION =
		"AudioConverter";

AudioConverterFilter::AudioConverterFilter():
		BaseConverterFilter(CONST_PLUGIN_NAME, CONST_PLUGIN_DESCRIPTION) {
	// TODO Auto-generated constructor stub
}

AudioConverterFilter::~AudioConverterFilter() {
	// TODO Auto-generated destructor stub
}

}
