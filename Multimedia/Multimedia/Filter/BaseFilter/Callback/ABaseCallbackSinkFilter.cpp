#include <Multimedia/Filter/BaseFilter/Callback/ABaseCallbackSinkFilter.h>
#include <Multimedia/Filter/BaseFilter/Callback/gstcallbackplugin.h>

namespace multimedia {

	const std::string ABaseCallbackSinkFilter::CONST_PLUGIN_NAME = "callbackplugin";
	const gboolean ABaseCallbackSinkFilter::CONST_FILTER_INITIALIZATION_STATE=ABaseCallbackSinkFilter::registerCallbackPlugin();


	gboolean ABaseCallbackSinkFilter::gstPluginInitMethod(GstPlugin* plugin){
		if(plugin==NULL){
			return FALSE;
		}

		gboolean result = gst_element_register(plugin, CONST_PLUGIN_NAME.c_str(), GST_RANK_NONE, GST_TYPE_CALLBACKPLUGIN);
		return result;
	}


	ABaseCallbackSinkFilter::ABaseCallbackSinkFilter(const std::string& description) : BaseSinkFilter(CONST_PLUGIN_NAME, description){
		g_object_set(G_OBJECT(_output.getPtr()), chain_callback_property, chainCallback, NULL);
		g_object_set(G_OBJECT(_output.getPtr()), setcaps_callback_property, setCapsCallback, NULL);
		g_object_set(G_OBJECT(_output.getPtr()), chain_callback_arg_property, this, NULL);
	}


	ABaseCallbackSinkFilter::~ABaseCallbackSinkFilter(void) {
		g_object_set(G_OBJECT(_output.getPtr()), chain_callback_property, NULL, NULL);
		g_object_set(G_OBJECT(_output.getPtr()), setcaps_callback_property, NULL, NULL);
	}


	gboolean ABaseCallbackSinkFilter::chainCallback(GstPad* gstPad, GstBuffer* gstBuffer, ABaseCallbackSinkFilter* _this) {
		if (_this != NULL) {
			if (!_this->onRecieveBuffer(gstPad, gstBuffer)) {
				return FALSE;
			}
		}

		return TRUE;
	}


	gboolean ABaseCallbackSinkFilter::setCapsCallback(GstPad * pad, GstCaps * caps, ABaseCallbackSinkFilter* _this) {
		if (_this != NULL) {
			if (!_this->onSetCaps(pad, caps)) {
				return FALSE;
			}
		}

		return TRUE;
	}


	gboolean ABaseCallbackSinkFilter::registerCallbackPlugin(){
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

