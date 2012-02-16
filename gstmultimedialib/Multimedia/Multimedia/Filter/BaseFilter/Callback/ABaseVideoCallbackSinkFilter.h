/*
 * ABaseVideoCallbackSinkFilter.h
 *
 *  Created on: Jul 9, 2011
 *      Author: alekstheod
 */

#ifndef ABASEVIDEOCALLBACKSINKFILTER_H_
#define ABASEVIDEOCALLBACKSINKFILTER_H_
#include <Multimedia/Utilities/GSmartPtr.h>
#include <string>
#include <gst/gst.h>
#include <Multimedia/GstException.h>
#include <Multimedia/Filter/BaseFilter/BaseSinkFilter.h>
#include <gst/base/gstbasesink.h>

namespace multimedia {

class ABaseVideoCallbackSinkFilter: public BaseSinkFilter {
public:
protected:
	virtual bool onRecieveBuffer(GstBaseSink* sink, GstBuffer* gstBuffer) = 0;
	virtual bool onSetCaps(GstPad * pad, GstCaps * caps) = 0;

public:
	static const std::string CONST_PLUGIN_NAME;

private:
	static const gboolean CONST_FILTER_INITIALIZATION_STATE;
	static gboolean registerCallbackPlugin();
	static gboolean renderCallback(GstBaseSink* sink, GstBuffer* gstBuffer,
			void* _this);
	static gboolean setCapsCallback(GstPad * pad, GstCaps * caps,
			void* _this);
	static gboolean gstPluginInitMethod(GstPlugin *plugin);
	friend class BasePlaybinFilterGraph;
	friend class BaseFilterGraph;
	static const GstPluginDesc CONST_PLUGIN_DESC;

public:
	ABaseVideoCallbackSinkFilter(const std::string& description);
	virtual ~ABaseVideoCallbackSinkFilter(void);
};

}

#endif /* ABASEVIDEOCALLBACKSINKFILTER_H_ */
