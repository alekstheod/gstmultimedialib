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
#include <Multimedia/Filter/BaseFilter/BaseOutputFilter.h>
#include <Multimedia/Exception/GstException.h>
#include <Multimedia/Filter/BaseFilter/IFilter.h>

namespace multimedia {

	class BaseConverterFilter: public IFilter {
		private:
			GSmartPtr<GstElement> _converter;

		private:
			friend class BaseDecoderFilter;
			friend class BasePlaybinFilterGraph;

		public:
			BaseConverterFilter(const std::string& pluginName, const std::string& description) throw (GstException);
			bool Connect(BaseOutputFilter* outputFilter);
			bool AddToPipeline(GstElement* pipeline);
			virtual ~BaseConverterFilter(void);
	};

}

#endif /* ACONVERTERFILTER_H_ */
