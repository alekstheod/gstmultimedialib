#ifndef BASECALLBACKSINK_H
#define BASECALLBACKSINK_H
#include <Multimedia/Utilities/GSmartPtr.h>
#include <string>
#include <gst/gst.h>
#include <Multimedia/Exception/GstException.h>
#include <Multimedia/Filter/BaseFilter/BaseSinkFilter.h>

namespace multimedia {

	class ABaseCallbackSink: public BaseSinkFilter {

		protected:
			virtual bool OnRecieveBuffer(GstPad* gstPad, GstBuffer* gstBuffer) = 0;
			virtual bool OnSetCaps(GstPad * pad, GstCaps * caps) = 0;

		public:
			static const std::string CONST_PLUGIN_NAME;

		private:
			static gboolean ChainCallback(GstPad* gstPad, GstBuffer* gstBuffer, ABaseCallbackSink* _this);
			static gboolean SetCapsCallback(GstPad * pad, GstCaps * caps, ABaseCallbackSink* _this);
			friend class BasePlaybinFilterGraph;
			friend class BaseFilterGraph;

		public:
			ABaseCallbackSink(const std::string& description);
			virtual ~ABaseCallbackSink(void);
	};

}

#endif // BASECALLBACKSINK_H
