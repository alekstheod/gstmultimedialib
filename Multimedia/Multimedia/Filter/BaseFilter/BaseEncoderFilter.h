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
#include <Multimedia/Filter/BaseFilter/IFilter.h>
#include <Multimedia/GstObject.h>

namespace multimedia {

	class BaseEncoderFilter : public IFilter, GstObject{
		private:
			GSmartPtr<GstElement> _encoder;

		private:
			friend class BasePlaybinFilterGraph;
			friend class BaseDecoderFilter;

		public:
			BaseEncoderFilter(const std::string& pluginName, const std::string& description) throw (GstException);
			bool addToPipeline(GstElement* pipeline);
			virtual ~BaseEncoderFilter(void);
	};

}

#endif /* BASEENCODERFILTER_H_ */
