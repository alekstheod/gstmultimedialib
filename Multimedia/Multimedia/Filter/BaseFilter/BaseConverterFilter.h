/*
 * BaseConverterFilter.h
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#ifndef ACONVERTERFILTER_H_
#define ACONVERTERFILTER_H_
#include <gst/gst.h>
#include <string>
#include <Multimedia/Filter/BaseFilter/BaseSinkFilter.h>
#include <Multimedia/GstException.h>
#include <Multimedia/Filter/BaseFilter/AFilter.h>
#include <Multimedia/GstObject.h>

namespace multimedia {

class BaseConverterFilter: public AFilter, GstObject {
private:
	GSmartPtr<GstElement> m_converter;

private:
	friend class BaseDecoderFilter;
	
	template<typename... FilterTypes>
	friend class BasePlaybinFilterGraph;

public:
	BaseConverterFilter(const std::string& pluginName,
			const std::string& description) throw (GstException);
	bool connect(BaseSinkFilter* outputFilter);
	bool addToPipeline(GstElement* pipeline);
	virtual ~BaseConverterFilter(void);
};

}

#endif /* ACONVERTERFILTER_H_ */
