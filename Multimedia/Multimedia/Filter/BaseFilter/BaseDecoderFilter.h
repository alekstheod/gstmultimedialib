/*
 * BaseDecoderFilter.h
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#ifndef ADECODERFILTER_H_
#define ADECODERFILTER_H_
#include <gst/gst.h>
#include "BaseConverterFilter.h"
#include "BaseOutputFilter.h"
#include <Multimedia/Filter/BaseFilter/BaseEncoderFilter.h>
#include <Multimedia/Filter/BaseFilter/IFilter.h>
#include <Multimedia/Utilities/GSmartPtr.h>

namespace multimedia {

	class BaseDecoderFilter: public IFilter {
		private:
			friend class BaseDemuxerFilter;
			friend class BasePlaybinFilterGraph;

		private:
			GSmartPtr<GstElement> _decoder;

		public:
			BaseDecoderFilter(const std::string& pluginName, const std::string& description) throw (GstException);
			bool Connect(BaseConverterFilter* converter);
			bool Connect(BaseOutputFilter* outputFilter);
			bool Connect(BaseEncoderFilter* encoderFilter);
			bool AddToPipeline(GstElement* pipeline);
			virtual ~BaseDecoderFilter(void);
	};

}

#endif /* ADECODERFILTER_H_ */
