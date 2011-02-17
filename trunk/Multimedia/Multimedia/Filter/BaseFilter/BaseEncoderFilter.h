/*
 * BaseEncoderFilter.h
 *
 *  Created on: Jul 10, 2010
 *      Author: m1cRo
 */

#ifndef BASEENCODERFILTER_H_
#define BASEENCODERFILTER_H_
#include <Multimedia/Exception/GstException.h>
#include <Multimedia/Utilities/GSmartPtr.h>

namespace multimedia {

	class BaseEncoderFilter {
		private:
			GSmartPtr<GstElement> _encoder;

		private:
			friend class BasePlaybinFilterGraph;
			friend class BaseDecoderFilter;

		public:
			BaseEncoderFilter(const std::string& pluginName, const std::string& description) throw (GstException);
			bool AddToPipeline(GstElement* pipeline);
			virtual ~BaseEncoderFilter(void);
	};

}

#endif /* BASEENCODERFILTER_H_ */
