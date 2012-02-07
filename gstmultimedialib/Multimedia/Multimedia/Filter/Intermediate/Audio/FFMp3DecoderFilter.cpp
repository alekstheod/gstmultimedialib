/*
 * FFMp3DecoderFilter.cpp
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#include <Multimedia/Filter/Intermediate/Audio/FFMp3DecoderFilter.h>

namespace multimedia {

const std::string FFMp3DecoderFilter::CONST_PLUGIN_NAME = "ffdec_mp3";
const std::string FFMp3DecoderFilter::CONST_PLUGIN_DESCRIPTION = "Mp3Decoder";

FFMp3DecoderFilter::FFMp3DecoderFilter(void) throw (GstException) :
		BaseDecoderFilter(CONST_PLUGIN_NAME, CONST_PLUGIN_DESCRIPTION) {
	// TODO Auto-generated constructor stub

}

FFMp3DecoderFilter::~FFMp3DecoderFilter(void) {
	// TODO Auto-generated destructor stub
}

}
