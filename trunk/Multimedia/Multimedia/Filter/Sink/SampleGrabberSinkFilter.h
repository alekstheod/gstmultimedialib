/*
 * SampleGrabberSinkFilter.h
 *
 *  Created on: Mar 19, 2011
 *      Author: m1cRo
 */

#ifndef SAMPLEGRABBERSINKFILTER_H_
#define SAMPLEGRABBERSINKFILTER_H_
#include <Multimedia/Filter/BaseFilter/Callback/ABaseCallbackSinkFilter.h>

namespace multimedia {

	class SampleGrabberSinkFilter : public ABaseCallbackSinkFilter {
		protected:
			virtual bool onRecieveBuffer(GstPad* gstPad, GstBuffer* gstBuffer);
			virtual bool onSetCaps(GstPad * pad, GstCaps * caps);

		public:
			SampleGrabberSinkFilter(const std::string& description);
			virtual ~SampleGrabberSinkFilter();
	};

}

#endif /* SAMPLEGRABBERSINKFILTER_H_ */
