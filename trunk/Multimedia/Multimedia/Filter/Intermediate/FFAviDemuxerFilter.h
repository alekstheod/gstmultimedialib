/*
 * FFAviDemuxerFilter.h
 *
 *  Created on: Jun 6, 2010
 *      Author: m1cro
 */

#ifndef FFAVIDEMUXERFILTER_H_
#define FFAVIDEMUXERFILTER_H_

#include <Multimedia/Filter/BaseFilter/BaseDemuxerFilter.h>

namespace multimedia {

class FFAviDemuxerFilter: public BaseDemuxerFilter {
public:
	static const std::string CONST_PLUGIN_NAME;
	static const std::string CONST_PLUGIN_DESCRIPTION;

public:
	FFAviDemuxerFilter() throw (GstException);
	virtual ~FFAviDemuxerFilter();
};

}

#endif /* FFAVIDEMUXERFILTER_H_ */
