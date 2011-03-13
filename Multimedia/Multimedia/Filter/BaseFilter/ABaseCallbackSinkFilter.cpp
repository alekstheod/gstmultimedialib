#include <Multimedia/Filter/BaseFilter/ABaseCallbackSinkFilter.h>

namespace multimedia {

	gboolean gst_plugin_init_function(GstPlugin *plugin){
		return TRUE;
	}

	const std::string ABaseCallbackSinkFilter::CONST_PLUGIN_NAME = "cbsink";
	const gboolean ABaseCallbackSinkFilter::CONST_IS_PLUGIN_INITIALIZED=gst_plugin_register_static(	GST_VERSION_MAJOR,
																								GST_VERSION_MINOR,
																								CONST_PLUGIN_NAME.c_str(),
																								"Callback sink plugin",
																								&gst_plugin_init_function,
																								"1.0.0",
																								"BSD",
																								"gstmultimedialib",
																								"gstmultimedialib",
																								"home");

	ABaseCallbackSinkFilter::ABaseCallbackSinkFilter(const std::string& description) : BaseSinkFilter(CONST_PLUGIN_NAME, description){
		/*g_object_set(G_OBJECT(_output.GetPtr()), "chain_callback", ChainCallback, NULL);
		g_object_set(G_OBJECT(_output.GetPtr()), "setcaps_callback", SetCapsCallback, NULL);
		g_object_set(G_OBJECT(_output.GetPtr()), "chain_callback_arg", this, NULL);*/


	}


	ABaseCallbackSinkFilter::~ABaseCallbackSinkFilter(void) {
		g_object_set(G_OBJECT(_output.GetPtr()), "chain_callback", NULL);
		g_object_set(G_OBJECT(_output.GetPtr()), "setcaps_callback", NULL);
	}


	gboolean ABaseCallbackSinkFilter::ChainCallback(GstPad* gstPad, GstBuffer* gstBuffer, ABaseCallbackSinkFilter* _this) {
		if (_this != NULL) {
			if (!_this->OnRecieveBuffer(gstPad, gstBuffer)) {
				return FALSE;
			}
		}

		return TRUE;
	}


	gboolean ABaseCallbackSinkFilter::SetCapsCallback(GstPad * pad, GstCaps * caps, ABaseCallbackSinkFilter* _this) {
		if (_this != NULL) {
			if (!_this->OnSetCaps(pad, caps)) {
				return FALSE;
			}
		}

		return TRUE;
	}

}

