/*
 * ABaseVideoCallbackSinkFilter.cpp
 *
 *  Created on: Jul 9, 2011
 *      Author: alekstheod
 */

#include <Multimedia/Filter/BaseFilter/Callback/ABaseVideoCallbackSinkFilter.h>
#include <Multimedia/Filter/BaseFilter/Callback/gstvideocallbackplugin.h>

namespace multimedia {

	const std::string ABaseVideoCallbackSinkFilter::CONST_PLUGIN_NAME = "videocallbackplugin";
	const gboolean ABaseVideoCallbackSinkFilter::CONST_FILTER_INITIALIZATION_STATE=ABaseVideoCallbackSinkFilter::registerCallbackPlugin();


	gboolean ABaseVideoCallbackSinkFilter::gstPluginInitMethod(GstPlugin* plugin){
		if(plugin==NULL){
			return FALSE;
		}

		gboolean result = gst_element_register(plugin, CONST_PLUGIN_NAME.c_str(), GST_RANK_NONE, GST_TYPE_VIDEO_CALLBACKPLUGIN);
		return result;
	}


	ABaseVideoCallbackSinkFilter::ABaseVideoCallbackSinkFilter(const std::string& description) : BaseSinkFilter(CONST_PLUGIN_NAME, description){
		g_object_set(G_OBJECT(_output.getPtr()), render_video_callback_property, renderCallback, NULL);
		g_object_set(G_OBJECT(_output.getPtr()), setcaps_video_callback_property, setCapsCallback, NULL);
		g_object_set(G_OBJECT(_output.getPtr()), chain_video_callback_arg_property, this, NULL);
	}


	ABaseVideoCallbackSinkFilter::~ABaseVideoCallbackSinkFilter(void) {
		g_object_set(G_OBJECT(_output.getPtr()), render_video_callback_property, NULL, NULL);
		g_object_set(G_OBJECT(_output.getPtr()), setcaps_video_callback_property, NULL, NULL);
	}


	gboolean ABaseVideoCallbackSinkFilter::renderCallback(GstBaseSink* sink, GstBuffer* gstBuffer, ABaseVideoCallbackSinkFilter* _this) {
		if (_this != NULL) {
			if (!_this->onRecieveBuffer(sink, gstBuffer)) {
				return FALSE;
			}
		}

		return TRUE;
	}


	gboolean ABaseVideoCallbackSinkFilter::setCapsCallback(GstPad * pad, GstCaps * caps, ABaseVideoCallbackSinkFilter* _this) {
		if (_this != NULL) {
			if (!_this->onSetCaps(pad, caps)) {
				return FALSE;
			}
		}

		return TRUE;
	}


	gboolean ABaseVideoCallbackSinkFilter::registerCallbackPlugin(){
		gst_init(NULL, NULL);
		return gst_plugin_register_static(	GST_VERSION_MAJOR,
											GST_VERSION_MINOR,
											CONST_PLUGIN_NAME.c_str(),
											"Callback sink plugin",
											gstPluginInitMethod,
											"1.0.0",
											"BSD",
											"gstmultimedialib",
											"gstmultimedialib",
											"http://www.google.com");
	}

}
