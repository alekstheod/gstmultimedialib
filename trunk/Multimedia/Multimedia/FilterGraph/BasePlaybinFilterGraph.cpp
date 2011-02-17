/*
 * BasePlayBinFilterGraph.cpp
 *
 *  Created on: Jul 3, 2010
 *      Author: m1cro
 */

#include "BasePlaybinFilterGraph.h"

namespace multimedia {

	const std::string BasePlaybinFilterGraph::CONST_PLAYBIN_PLUGIN_NAME = "playbin2";
	const std::string BasePlaybinFilterGraph::CONST_PLAYBIN_PLUGIN_DESCRIPTION = "Player";

	BasePlaybinFilterGraph::BasePlaybinFilterGraph(const std::string& fileName) throw (GstException) :
		CONST_FILE_NAME(fileName) {
		_mainLoop = g_main_loop_new(NULL, FALSE);
		if (_mainLoop == NULL) {
			throw GstException("BaseFilterGraph::BaseFilterGraph - Create MainLoop failed");
		}

		_pipeline = gst_element_factory_make(CONST_PLAYBIN_PLUGIN_NAME.c_str(), CONST_PLAYBIN_PLUGIN_DESCRIPTION.c_str());
		if (_pipeline == NULL) {
			throw GstException("BasePlaybinFilterGraph::BasePlaybinFilterGraph - Create pipeline failed");
		}

		g_object_set(G_OBJECT(_pipeline.GetPtr()), "uri", CONST_FILE_NAME.c_str(), NULL);

		GstBus* bus = gst_pipeline_get_bus(GST_PIPELINE(_pipeline.GetPtr()));
		gst_bus_add_watch(bus, MainLoop, _mainLoop);
		gst_object_unref(bus);
	}

	gboolean BasePlaybinFilterGraph::MainLoop(GstBus* bus, GstMessage* msg, gpointer data) {
		GMainLoop* loop = (GMainLoop*) data;

		switch (GST_MESSAGE_TYPE(msg)) {

			case GST_MESSAGE_EOS:
				g_print("End of stream\n");
				g_main_loop_quit(loop);
				break;

			case GST_MESSAGE_ERROR: {
				gchar* debug;
				GError* error;

				gst_message_parse_error(msg, &error, &debug);
				g_free(debug);

				g_printerr("Error: %s\n", error->message);
				g_error_free(error);

				g_main_loop_quit(loop);
				break;
			}
			default:
				break;
		}

		return TRUE;
	}

	bool SetEncoder(BaseEncoderFilter* encoder) {
		return false;
	}

	bool BasePlaybinFilterGraph::SetAudioSink(BaseOutputFilter* audioSink) {
		if (audioSink == NULL) {
			return false;
		}

		g_object_set(G_OBJECT(_pipeline.GetPtr()), "audio-sink", audioSink->_output.GetPtr(), NULL);
		return true;
	}

	bool BasePlaybinFilterGraph::SetVideoSink(BaseOutputFilter* videoSink) {
		if (videoSink == NULL) {
			return false;
		}

		g_object_set(G_OBJECT(_pipeline.GetPtr()), "video-sink", videoSink->_output.GetPtr(), NULL);
		return true;
	}

	bool BasePlaybinFilterGraph::SetAudioSink(BaseCallbackSink* audioSink) {
		if (audioSink == NULL) {
			return false;
		}

		//g_object_set(G_OBJECT(_pipeline.GetPtr()),"audio-sink",audioSink->_cbSink.GetPtr(),NULL);
		return true;
	}

	bool BasePlaybinFilterGraph::SetVideoSink(BaseCallbackSink* videoSink) {
		if (videoSink == NULL) {
			return false;
		}

		g_object_set(G_OBJECT(_pipeline.GetPtr()), "video-sink", videoSink->_cbSink.GetPtr(), NULL);
		return true;
	}

	bool BasePlaybinFilterGraph::Play(void) {
		GstStateChangeReturn ret = gst_element_set_state(_pipeline.GetPtr(), GST_STATE_PLAYING);
		if (ret == GST_STATE_CHANGE_FAILURE) {
			return false;
		}

		g_main_loop_run(_mainLoop);
		return true;
	}

	bool BasePlaybinFilterGraph::Stop(void) {
		return false;
	}

	bool BasePlaybinFilterGraph::Rewind(void) {
		return false;
	}

	BasePlaybinFilterGraph::~BasePlaybinFilterGraph() {
		if (_mainLoop != NULL) {
			g_main_loop_unref(_mainLoop);
		}
	}

}

