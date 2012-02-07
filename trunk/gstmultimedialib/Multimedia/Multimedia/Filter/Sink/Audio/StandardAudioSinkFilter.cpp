/*
 * StandardAudioOutputFilter.cpp
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#include <Multimedia/Filter/Sink/Audio/StandardAudioSinkFilter.h>

namespace multimedia {

const std::string StandardAudioSinkFilter::CONST_PLUGIN_NAME = "autoaudiosink";

StandardAudioSinkFilter::StandardAudioSinkFilter(const std::string& description)
		throw (GstException) :
		BaseSinkFilter(CONST_PLUGIN_NAME, description) {
	// TODO Auto-generated constructor stub

}

StandardAudioSinkFilter::~StandardAudioSinkFilter(void) {
	// TODO Auto-generated destructor stub
}

}
