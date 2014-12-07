/*
 * XVideoImageSink.h
 *
 *  Created on: Feb 23, 2011
 *      Author: m1cRo
 */

#ifndef XVIDEOIMAGESINK_H_
#define XVIDEOIMAGESINK_H_

#include <Multimedia/Filter/BaseFilter/BaseSinkFilter.h>

namespace multimedia {

class XVideoImageSink: public multimedia::BaseSinkFilter {
public:
	static const std::string CONST_PLUGIN_NAME;

public:
	XVideoImageSink(const std::string& description) throw (GstException);
	XVideoImageSink(const std::string& description, gulong xWindowId)
			throw (GstException);
	virtual ~XVideoImageSink();
};

}

#endif /* XVIDEOIMAGESINK_H_ */
