#ifndef BASECALLBACKSINK_H
#define BASECALLBACKSINK_H
#include <Multimedia/Utilities/GSmartPtr.h>
#include <string>
#include <gst/gst.h>
#include <Multimedia/Exception/GstException.h>
#include <Multimedia/Filter/BaseFilter/BaseSinkFilter.h>

namespace multimedia {

	class BaseCallbackSink: public BaseSinkFilter {

		protected:
			virtual bool OnRecieveBuffer(GstPad* gstPad, GstBuffer* gstBuffer) = 0;
			virtual bool OnSetCaps(GstPad * pad, GstCaps * caps) = 0;

		public:
			static const std::string CONST_PLUGIN_NAME;

		private:
			static gboolean ChainCallback(GstPad* gstPad, GstBuffer* gstBuffer, BaseCallbackSink* _this);
			static gboolean SetCapsCallback(GstPad * pad, GstCaps * caps, BaseCallbackSink* _this);
			friend class BasePlaybinFilterGraph;
			friend class BaseFilterGraph;

		public:
			BaseCallbackSink(const std::string& description);
			virtual ~BaseCallbackSink(void);
	};

}

#endif // BASECALLBACKSINK_H
