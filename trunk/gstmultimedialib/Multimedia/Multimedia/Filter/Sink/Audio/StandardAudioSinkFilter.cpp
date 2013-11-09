/*
 * StandardAudioOutputFilter.cpp
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#include <Multimedia/Filter/Sink/Audio/StandardAudioSinkFilter.h>

namespace multimedia {

const std::string StandardAudioSinkFilter::CONST_PLUGIN_NAME = "autoaudiosink";
 const std::string StandardAudioSinkFilter::CONST_SINK_TYPE = "audio";

StandardAudioSinkFilter::StandardAudioSinkFilter(const std::string& description)
		throw (GstException) :
		_baseSink(CONST_PLUGIN_NAME, description) {
	// TODO Auto-generated constructor stub

}

bool StandardAudioSinkFilter::addToPipelineImpl ( GstElement* pipeline )
{
  return _baseSink.addToPipeline(pipeline, CONST_SINK_TYPE);
}

StandardAudioSinkFilter::~StandardAudioSinkFilter(void) {
	// TODO Auto-generated destructor stub
}

}
