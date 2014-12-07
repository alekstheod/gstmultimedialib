/*
 * FFMp3DemuxerFilter.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#include <Multimedia/Filter/Intermediate/Audio/FFMp3DemuxerFilter.h>

namespace multimedia {

const std::string FFMp3DemuxerFilter::CONST_PLUGIN_NAME = "ffdemux_mp3";
const std::string FFMp3DemuxerFilter::CONST_PLUGIN_DESCRIPTION = "demuxer";

FFMp3DemuxerFilter::FFMp3DemuxerFilter(void) throw (GstException) :
		BaseDemuxerFilter(CONST_PLUGIN_NAME, CONST_PLUGIN_DESCRIPTION) {

}

FFMp3DemuxerFilter::~FFMp3DemuxerFilter(void) {
}

}

