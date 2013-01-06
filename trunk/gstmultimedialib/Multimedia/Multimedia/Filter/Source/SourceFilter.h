/*
 * SourceFilter.h
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#ifndef SOURCEFILTER_H_
#define SOURCEFILTER_H_
#include <gst/gst.h>
#include <Multimedia/GstException.h>
#include <Multimedia/Filter/BaseFilter/BaseDemuxerFilter.h>
#include <Multimedia/Filter/BaseFilter/IFilter.h>
#include <Multimedia/Filter/BaseFilter/IFilter.h>

namespace multimedia {

class BaseSinkFilter;

class SourceFilter: public IFilter {
private:
	GSmartPtr<GstElement> _source;

public:
	static const std::string CONST_PLUGIN_NAME;

public:
	SourceFilter(const std::string& fileName);
	bool Connect(BaseDemuxerFilter* demuxer);
	bool Connect(BaseSinkFilter* output);
	bool addToPipeline(GstElement* pipeline);
	virtual ~SourceFilter(void);
};

}

#endif /* SOURCEFILTER_H_ */
