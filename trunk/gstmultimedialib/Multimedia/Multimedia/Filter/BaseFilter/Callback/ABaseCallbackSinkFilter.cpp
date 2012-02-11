#include <Multimedia/Filter/BaseFilter/Callback/ABaseCallbackSinkFilter.h>
#include <Multimedia/Filter/BaseFilter/Callback/gstcallbackplugin.h>

namespace multimedia {

const std::string ABaseCallbackSinkFilter::CONST_PLUGIN_NAME = "callbackplugin";
const gboolean ABaseCallbackSinkFilter::CONST_FILTER_INITIALIZATION_STATE =
		ABaseCallbackSinkFilter::registerCallbackPlugin();
int operator==(GstPlugin & plugin, const int & i) {
	return int();
}

gboolean ABaseCallbackSinkFilter::gstPluginInitMethod(GstPlugin* plugin) {
	if (plugin) {
		return gst_element_register(plugin, CONST_PLUGIN_NAME.c_str(),
				GST_RANK_NONE, GST_TYPE_CALLBACKPLUGIN);

	}

	return FALSE;
}

ABaseCallbackSinkFilter::ABaseCallbackSinkFilter(const std::string& description) :
		BaseSinkFilter(CONST_PLUGIN_NAME, description) {
	g_object_set(G_OBJECT(_output.getPtr()), chain_callback_property,
			chainCallback, NULL);
	g_object_set(G_OBJECT(_output.getPtr()), setcaps_callback_property,
			setCapsCallback, NULL);
	g_object_set(G_OBJECT(_output.getPtr()), chain_callback_arg_property, this,
			NULL);
}

ABaseCallbackSinkFilter::~ABaseCallbackSinkFilter(void) {
	g_object_set(G_OBJECT(_output.getPtr()), chain_callback_property, NULL,
			NULL);
	g_object_set(G_OBJECT(_output.getPtr()), setcaps_callback_property, NULL,
			NULL);
}

gboolean ABaseCallbackSinkFilter::chainCallback(GstPad* gstPad,
		GstBuffer* gstBuffer, GstCookie* _this) {
	gboolean result = FALSE;
	ABaseCallbackSinkFilter* __this = static_cast< ABaseCallbackSinkFilter* > (_this);
	if (__this) {
		if (__this->onRecieveBuffer(gstPad, gstBuffer)) {
			result = TRUE;
		}
	}

	return result;
}

gboolean ABaseCallbackSinkFilter::setCapsCallback(GstPad * pad, GstCaps * caps,
		GstCookie* _this) {
	gboolean result = FALSE;
	ABaseCallbackSinkFilter* __this = static_cast< ABaseCallbackSinkFilter* > (_this);
	if (__this) {
		if (__this->onSetCaps(pad, caps)) {
			result = TRUE;
		}
	}

	return result;
}

gboolean ABaseCallbackSinkFilter::registerCallbackPlugin() {
	return gst_plugin_register_static(GST_VERSION_MAJOR, GST_VERSION_MINOR,
			CONST_PLUGIN_NAME.c_str(), "Callback sink plugin",
			gstPluginInitMethod, "1.0.0", "BSD", "gstmultimedialib",
			"gstmultimedialib", "http://www.google.com");
}

}

