#include <Multimedia/Filter/BaseFilter/ABaseCallbackSinkFilter.h>

namespace multimedia {

	gboolean ABaseCallbackSinkFilter::gstPluginInitMethod(GstPlugin *plugin){
		if(plugin==NULL){
			return FALSE;
		}

		gboolean result = gst_element_register(plugin, CONST_PLUGIN_NAME.c_str(), GST_RANK_NONE, GST_TYPE_ELEMENT);
		return result;
	}


	const std::string ABaseCallbackSinkFilter::CONST_PLUGIN_NAME = "cbsink";


	ABaseCallbackSinkFilter::ABaseCallbackSinkFilter(const std::string& description) : BaseSinkFilter(CONST_PLUGIN_NAME, description){
		/*g_object_set(G_OBJECT(_output.GetPtr()), "chain_callback", ChainCallback, NULL);
		g_object_set(G_OBJECT(_output.GetPtr()), "setcaps_callback", SetCapsCallback, NULL);
		g_object_set(G_OBJECT(_output.GetPtr()), "chain_callback_arg", this, NULL);*/
	}


	ABaseCallbackSinkFilter::~ABaseCallbackSinkFilter(void) {
		g_object_set(G_OBJECT(_output.getPtr()), "chain_callback", NULL);
		g_object_set(G_OBJECT(_output.getPtr()), "setcaps_callback", NULL);
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

