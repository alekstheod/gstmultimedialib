/*
 * ABaseVideoCallbackSinkFilter.cpp
 *
 *  Created on: Jul 9, 2011
 *      Author: alekstheod
 */

#include <Multimedia/Filter/Sink/Video/ABaseVideoCallbackSinkFilter.h>
#include <Multimedia/Filter/BaseFilter/Callback/gstvideocallbackplugin.h>

namespace multimedia
{

const char* ABaseVideoCallbackSinkFilter::CONST_FILTER_TYPE = "video";

const std::string ABaseVideoCallbackSinkFilter::CONST_PLUGIN_NAME =
  "videocallbackplugin";
const gboolean ABaseVideoCallbackSinkFilter::CONST_FILTER_INITIALIZATION_STATE =
  ABaseVideoCallbackSinkFilter::registerCallbackPlugin();

gboolean ABaseVideoCallbackSinkFilter::gstPluginInitMethod ( GstPlugin* plugin )
{
  if ( plugin == NULL )
    {
      return FALSE;
    }

  gboolean result = gst_element_register ( plugin, CONST_PLUGIN_NAME.c_str(),
                    GST_RANK_NONE, GST_TYPE_VIDEO_CALLBACKPLUGIN );
  return result;
}

ABaseVideoCallbackSinkFilter::ABaseVideoCallbackSinkFilter (const std::string& description) :
  m_baseSinkFilter ( CONST_PLUGIN_NAME, description )
{
  m_baseSinkFilter.setObject ( render_video_callback_property, renderCallback );
  m_baseSinkFilter.setObject ( setcaps_video_callback_property, setCapsCallback );
  m_baseSinkFilter.setObject ( chain_video_callback_arg_property, this );
}

ABaseVideoCallbackSinkFilter::~ABaseVideoCallbackSinkFilter ( )
{
  m_baseSinkFilter.setObject ( render_video_callback_property, NULL );
  m_baseSinkFilter.setObject ( setcaps_video_callback_property, NULL );
  m_baseSinkFilter.setObject ( chain_video_callback_arg_property, NULL );
}

bool ABaseVideoCallbackSinkFilter::addToPipelineImpl ( GstElement* pipeline )
{
  return m_baseSinkFilter.addToPipeline ( pipeline, CONST_FILTER_TYPE );
}

gboolean ABaseVideoCallbackSinkFilter::renderCallback ( GstBaseSink* sink,
    GstBuffer* gstBuffer, void* _this )
{
  gboolean result = FALSE;
  ABaseVideoCallbackSinkFilter* this_ = ( ABaseVideoCallbackSinkFilter* ) ( _this );
  if ( this_ != NULL )
    {
      if ( this_->onRecieveBuffer( sink, gstBuffer ) )
        {
          result = TRUE;
        }
    }

  return result;
}

gboolean ABaseVideoCallbackSinkFilter::setCapsCallback ( GstPad * pad,
    GstCaps * caps, void* _this )
{
  gboolean result = FALSE;
  ABaseVideoCallbackSinkFilter* this_ = ( ABaseVideoCallbackSinkFilter* ) ( _this );
  if ( this_ != NULL )
    {
      if ( this_->onSetCaps ( pad, caps ) )
        {
          result = TRUE;
        }
    }

  return result;
}

gboolean ABaseVideoCallbackSinkFilter::registerCallbackPlugin()
{
  gst_init ( NULL, NULL );
  return gst_plugin_register_static ( GST_VERSION_MAJOR, GST_VERSION_MINOR,
                                      CONST_PLUGIN_NAME.c_str(), "Callback sink plugin",
                                      gstPluginInitMethod, "1.0.0", "BSD", "gstmultimedialib",
                                      "gstmultimedialib", "http://www.google.com" );
}

}
