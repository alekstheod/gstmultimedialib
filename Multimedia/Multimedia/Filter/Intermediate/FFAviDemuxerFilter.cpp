/*
 * FFAviDemuxerFilter.cpp
 *
 *  Created on: Jun 6, 2010
 *      Author: m1cro
 */

#include <Multimedia/Filter/Intermediate/FFAviDemuxerFilter.h>

namespace multimedia {

	const std::string FFAviDemuxerFilter::CONST_PLUGIN_NAME = "ffdemux_avi";
	const std::string FFAviDemuxerFilter::CONST_PLUGIN_DESCRIPTION = "AviDemuxer";

	FFAviDemuxerFilter::FFAviDemuxerFilter() throw (GstException) :
		BaseDemuxerFilter(CONST_PLUGIN_NAME, CONST_PLUGIN_DESCRIPTION) {
		// TODO Auto-generated constructor stub

	}

	FFAviDemuxerFilter::~FFAviDemuxerFilter() {
		// TODO Auto-generated destructor stub
	}

}

