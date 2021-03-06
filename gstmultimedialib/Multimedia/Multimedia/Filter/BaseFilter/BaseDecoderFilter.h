/*
 * BaseDecoderFilter.h
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#ifndef ADECODERFILTER_H_
#define ADECODERFILTER_H_
#include <gst/gst.h>
#include <Multimedia/Filter/BaseFilter/BaseConverterFilter.h>
#include <Multimedia/Filter/BaseFilter/BaseSinkFilter.h>
#include <Multimedia/Filter/BaseFilter/BaseEncoderFilter.h>
#include <Multimedia/Filter/BaseFilter/AFilter.h>
#include <Multimedia/Utilities/GSmartPtr.h>
#include <Multimedia/GstObject.h>

namespace multimedia {

class BaseDecoderFilter: public AFilter, GstObject {
private:
	friend class BaseDemuxerFilter;
	
	template<typename... FilterTypes>
	friend class BasePlaybinFilterGraph;

private:
	GSmartPtr<GstElement> m_decoder;

public:
	BaseDecoderFilter(const std::string& pluginName,
			const std::string& description) throw (GstException);
	bool connect(BaseConverterFilter* converter);
	bool connect(BaseSinkFilter* outputFilter);
	bool connect(BaseEncoderFilter* encoderFilter);
	bool addToPipeline(GstElement* pipeline);
	virtual ~BaseDecoderFilter(void);
};

}

#endif /* ADECODERFILTER_H_ */
