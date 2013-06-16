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
#include <Multimedia/Filter/BaseFilter/AFilter.h>

namespace multimedia
{

class ABaseVideoCallbackSinkFilter : public AFilter
{
public:
  static const char* CONST_FILTER_TYPE;
  BaseSinkFilter _baseSinkFilter;

protected:
  virtual bool onRecieveBuffer ( GstBaseSink* sink, GstBuffer* gstBuffer ) =0;
  virtual bool onSetCaps ( GstPad * pad, GstCaps * caps ) =0;

public:
  static const std::string CONST_PLUGIN_NAME;

private:
  static const gboolean CONST_FILTER_INITIALIZATION_STATE;
  static gboolean registerCallbackPlugin();
  static gboolean renderCallback ( GstBaseSink* sink, GstBuffer* gstBuffer,void* _this );
  static gboolean setCapsCallback ( GstPad * pad, GstCaps * caps, void* _this );
  static gboolean gstPluginInitMethod ( GstPlugin *plugin );
  
  static const GstPluginDesc CONST_PLUGIN_DESC;

public:
  ABaseVideoCallbackSinkFilter ( const std::string& description );
  bool addToPipeline ( GstElement* pipeline ) ;
  virtual ~ABaseVideoCallbackSinkFilter ( );
};

}

#endif /* ABASEVIDEOCALLBACKSINKFILTER_H_ */
// kate: indent-mode cstyle; indent-width 2; replace-tabs on; 
