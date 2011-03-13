#include <Multimedia/Filter/BaseFilter/ABaseCallbackSink.h>

namespace multimedia {

	const std::string ABaseCallbackSink::CONST_PLUGIN_NAME = "cbsink";

	ABaseCallbackSink::ABaseCallbackSink(const std::string& description) : BaseSinkFilter(CONST_PLUGIN_NAME, description){
		g_object_set(G_OBJECT(_output.GetPtr()), "chain_callback", ChainCallback, NULL);
		g_object_set(G_OBJECT(_output.GetPtr()), "setcaps_callback", SetCapsCallback, NULL);
		g_object_set(G_OBJECT(_output.GetPtr()), "chain_callback_arg", this, NULL);
	}


	ABaseCallbackSink::~ABaseCallbackSink(void) {
		g_object_set(G_OBJECT(_output.GetPtr()), "chain_callback", NULL);
		g_object_set(G_OBJECT(_output.GetPtr()), "setcaps_callback", NULL);
	}


	gboolean ABaseCallbackSink::ChainCallback(GstPad* gstPad, GstBuffer* gstBuffer, ABaseCallbackSink* _this) {
		if (_this != NULL) {
			if (!_this->OnRecieveBuffer(gstPad, gstBuffer)) {
				return FALSE;
			}
		}

		return TRUE;
	}


	gboolean ABaseCallbackSink::SetCapsCallback(GstPad * pad, GstCaps * caps, ABaseCallbackSink* _this) {
		if (_this != NULL) {
			if (!_this->OnSetCaps(pad, caps)) {
				return FALSE;
			}
		}

		return TRUE;
	}

}

