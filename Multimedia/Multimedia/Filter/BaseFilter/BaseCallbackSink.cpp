#include <Multimedia/Filter/BaseFilter/BaseCallbackSink.h>

namespace multimedia {

	const std::string BaseCallbackSink::CONST_PLUGIN_NAME = "cbsink";

	BaseCallbackSink::BaseCallbackSink(const std::string& description) : BaseSinkFilter(CONST_PLUGIN_NAME, description){
		g_object_set(G_OBJECT(_output.GetPtr()), "chain_callback", ChainCallback, NULL);
		g_object_set(G_OBJECT(_output.GetPtr()), "setcaps_callback", SetCapsCallback, NULL);
		g_object_set(G_OBJECT(_output.GetPtr()), "chain_callback_arg", this, NULL);
	}


	BaseCallbackSink::~BaseCallbackSink(void) {
		g_object_set(G_OBJECT(_output.GetPtr()), "chain_callback", NULL);
		g_object_set(G_OBJECT(_output.GetPtr()), "setcaps_callback", NULL);
	}


	gboolean BaseCallbackSink::ChainCallback(GstPad* gstPad, GstBuffer* gstBuffer, BaseCallbackSink* _this) {
		if (_this != NULL) {
			if (!_this->OnRecieveBuffer(gstPad, gstBuffer)) {
				return FALSE;
			}
		}

		return TRUE;
	}


	gboolean BaseCallbackSink::SetCapsCallback(GstPad * pad, GstCaps * caps, BaseCallbackSink* _this) {
		if (_this != NULL) {
			if (!_this->OnSetCaps(pad, caps)) {
				return FALSE;
			}
		}

		return TRUE;
	}

}

