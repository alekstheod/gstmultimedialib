/*
 * BaseEncoderFilter.h
 *
 *  Created on: Jul 10, 2010
 *      Author: m1cRo
 */

#ifndef BASEENCODERFILTER_H_
#define BASEENCODERFILTER_H_
#include <Multimedia/GstException.h>
#include <Multimedia/Utilities/GSmartPtr.h>
#include <Multimedia/Filter/BaseFilter/AFilter.h>
#include <Multimedia/GstObject.h>

namespace multimedia {

class BaseEncoderFilter: public AFilter, GstObject {
private:
	GSmartPtr<GstElement> m_encoder;

private:
        template<typename... FilterTypes>
	friend class BasePlaybinFilterGraph;
	friend class BaseDecoderFilter;

public:
	BaseEncoderFilter(const std::string& pluginName,
			const std::string& description) throw (GstException);
	bool addToPipeline(GstElement* pipeline);
	virtual ~BaseEncoderFilter();
};

}

#endif /* BASEENCODERFILTER_H_ */
