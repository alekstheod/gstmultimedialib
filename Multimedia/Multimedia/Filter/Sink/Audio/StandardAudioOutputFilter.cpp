/*
 * StandardAudioOutputFilter.cpp
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#include <Multimedia/Filter/Sink/Audio/StandardAudioOutputFilter.h>

namespace multimedia{

	const std::string StandardAudioOutputFilter::CONST_PLUGIN_NAME = "autoaudiosink";
	const std::string StandardAudioOutputFilter::CONST_PLUGIN_DESCRIPTION = "Audio-Out";

	StandardAudioOutputFilter::StandardAudioOutputFilter(void)throw (GstException) : BaseOutputFilter(CONST_PLUGIN_NAME, CONST_PLUGIN_DESCRIPTION) {
	    // TODO Auto-generated constructor stub

	}

	StandardAudioOutputFilter::~StandardAudioOutputFilter(void) {
	    // TODO Auto-generated destructor stub
	}

}
