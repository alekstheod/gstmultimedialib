#ifndef BASECALLBACKSINK_H
#define BASECALLBACKSINK_H
#include <Multimedia/Utilities/GSmartPtr.h>
#include <string>
#include <gst/gst.h>
#include <Multimedia/GstException.h>
#include <Multimedia/Filter/BaseFilter/BaseSinkFilter.h>
#include <Multimedia/Filter/BaseFilter/Callback/GstCookie.h>

namespace multimedia {

class ABaseCallbackSinkFilter: public BaseSinkFilter, GstCookie {
protected:
	virtual bool onRecieveBuffer(GstPad* gstPad, GstBuffer* gstBuffer) = 0;
	virtual bool onSetCaps(GstPad * pad, GstCaps * caps) = 0;

public:
	static const std::string CONST_PLUGIN_NAME;

private:
	static const gboolean CONST_FILTER_INITIALIZATION_STATE;
	static gboolean registerCallbackPlugin();
	static gboolean chainCallback(GstPad* gstPad, GstBuffer* gstBuffer,
			GstCookie* _this);
	static gboolean setCapsCallback(GstPad * pad, GstCaps * caps,
			GstCookie* _this);
	static gboolean gstPluginInitMethod(GstPlugin *plugin);
	friend class BasePlaybinFilterGraph;
	friend class BaseFilterGraph;
	static const GstPluginDesc CONST_PLUGIN_DESC;

public:
	ABaseCallbackSinkFilter(const std::string& description);
	virtual ~ABaseCallbackSinkFilter(void);
};

}

#endif // BASECALLBACKSINK_H
