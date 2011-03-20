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

		g_object_set(G_OBJECT(_pipeline.getPtr()), "uri", CONST_FILE_NAME.c_str(), NULL);

		GstBus* bus = gst_pipeline_get_bus(GST_PIPELINE(_pipeline.getPtr()));
		gst_bus_add_watch(bus, mainLoop, _mainLoop);
		gst_object_unref(bus);
	}

	gboolean BasePlaybinFilterGraph::mainLoop(GstBus* bus, GstMessage* msg, gpointer data) {
		GMainLoop* loop = (GMainLoop*) data;

		switch (GST_MESSAGE_TYPE(msg)) {

			case GST_MESSAGE_EOS:{
				g_print("End of stream\n");
				g_main_loop_quit(loop);
			}break;

			case GST_MESSAGE_ERROR: {
				gchar* debug;
				GError* error;

				gst_message_parse_error(msg, &error, &debug);
				g_free(debug);

				g_printerr("Error: %s\n", error->message);
				g_error_free(error);

				g_main_loop_quit(loop);

			}break;

			default:{
			}break;
		}

		return TRUE;
	}


	bool SetEncoder(BaseEncoderFilter* encoder) {
		return false;
	}


	bool BasePlaybinFilterGraph::setAudioSink(BaseSinkFilter* audioSink) {
		if (audioSink == NULL) {
			return false;
		}

		g_object_set(G_OBJECT(_pipeline.getPtr()), "audio-sink", audioSink->_output.getPtr(), NULL);
		return true;
	}


	bool BasePlaybinFilterGraph::setVideoSink(BaseSinkFilter* videoSink) {
		if (videoSink == NULL) {
			return false;
		}

		g_object_set(G_OBJECT(_pipeline.getPtr()), "video-sink", videoSink->_output.getPtr(), NULL);
		return true;
	}


	bool BasePlaybinFilterGraph::play(void) {
		GstStateChangeReturn ret = gst_element_set_state(_pipeline.getPtr(), GST_STATE_PLAYING);
		if (ret == GST_STATE_CHANGE_FAILURE) {
			return false;
		}

		g_main_loop_run(_mainLoop);
		return true;
	}


	bool BasePlaybinFilterGraph::stop(void) {
		GstStateChangeReturn ret = gst_element_set_state(_pipeline.getPtr(), GST_STATE_READY);
		if (ret == GST_STATE_CHANGE_FAILURE) {
			return false;
		}

		g_main_loop_quit(_mainLoop);
		return true;
	}

	bool BasePlaybinFilterGraph::rewind(void) {
		return false;
	}


	BasePlaybinFilterGraph::~BasePlaybinFilterGraph() {
		if (_mainLoop != NULL) {
			g_main_loop_unref(_mainLoop);
		}
	}

}

