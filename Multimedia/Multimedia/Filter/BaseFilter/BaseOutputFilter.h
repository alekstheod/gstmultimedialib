/*
 * BaseOutputFilter.h
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#ifndef AOUTPUTFILTER_H_
#define AOUTPUTFILTER_H_
#include <gst/gst.h>
#include <string>
#include <Multimedia/Exception/GstException.h>
#include <Multimedia/Filter/BaseFilter/IFilter.h>
#include <Multimedia/Utilities/GSmartPtr.h>

namespace multimedia {

	class BaseOutputFilter: public IFilter {
		protected:
			GSmartPtr<GstElement> _output;

		private:
			friend class BaseConverterFilter;
			friend class BaseDecoderFilter;
			friend class SourceFilter;
			friend class BasePlaybinFilterGraph;

		public:
			BaseOutputFilter(const std::string& pluginName, const std::string& description) throw (GstException);
			bool AddToPipeline(GstElement* pipeline);
			virtual ~BaseOutputFilter(void);
	};

}

#endif /* AOUTPUTFILTER_H_ */
