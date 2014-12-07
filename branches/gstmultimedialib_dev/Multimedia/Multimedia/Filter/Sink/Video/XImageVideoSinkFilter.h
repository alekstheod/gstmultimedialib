/*
 * ImageVideoSink.h
 *
 *  Created on: Feb 23, 2011
 *      Author: m1cRo
 */

#ifndef IMAGEVIDEOSINK_H_
#define IMAGEVIDEOSINK_H_

#include <Multimedia/Filter/BaseFilter/BaseSinkFilter.h>

namespace multimedia {

class XImageVideoSinkFilter: public multimedia::BaseSinkFilter {
public:
	static const std::string CONST_PLUGIN_NAME;

public:
	XImageVideoSinkFilter(const std::string& description);
	virtual ~XImageVideoSinkFilter();
};

}

#endif /* IMAGEVIDEOSINK_H_ */
