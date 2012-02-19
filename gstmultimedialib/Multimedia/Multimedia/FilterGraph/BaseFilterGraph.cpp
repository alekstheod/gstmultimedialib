/*
 * BaseFilterGraph.cpp
 *
 *  Created on: Jun 6, 2010
 *      Author: m1cro
 */

#include <Multimedia/FilterGraph/BaseFilterGraph.h>

namespace multimedia {

BaseFilterGraph::BaseFilterGraph(const std::string& graphName)
		throw (GstException) {
	if (graphName.empty()) {
		throw GstException(
				"BaseFilterGraph::BaseFilterGraph - Wrong argument graphName");
	}

	_mainLoop = g_main_loop_new(NULL, FALSE);
	if (_mainLoop == NULL) {
		throw GstException(
				"BaseFilterGraph::BaseFilterGraph - Create MainLoop failed");
	}

	_pipeline = gst_pipeline_new("Mp3-Player");
	if (_pipeline == NULL) {
		throw GstException(
				"BaseFilterGraph::BaseFilterGraph - Create pipeline failed");
	}

	GstBus* bus = gst_pipeline_get_bus(GST_PIPELINE(_pipeline.getPtr()));
	gst_bus_add_watch(bus, MainLoop, _mainLoop);
	gst_object_unref(bus);
}

gboolean BaseFilterGraph::MainLoop(GstBus *bus, GstMessage *msg,
		gpointer data) {
	GMainLoop *loop = (GMainLoop *) data;

	switch(GST_MESSAGE_TYPE(msg)) {

		case GST_MESSAGE_EOS:
		g_print("End of stream\n");
		g_main_loop_quit(loop);
		break;

		case GST_MESSAGE_ERROR:
		{
			gchar *debug;
			GError *error;

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

bool BaseFilterGraph::addFilter(IFilter* filter) {
	if (filter == NULL) {
		return false;
	}

	return filter->addToPipeline(_pipeline.getPtr());
}

bool BaseFilterGraph::play(void) {
	GstStateChangeReturn ret = gst_element_set_state(_pipeline.getPtr(),
			GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE) {
		return false;
	}
	
	g_main_loop_run(_mainLoop);
	return true;
}

bool BaseFilterGraph::stop(void) {
	GstStateChangeReturn ret = gst_element_set_state(_pipeline.getPtr(),
			GST_STATE_READY);
	if (ret == GST_STATE_CHANGE_FAILURE) {
		return false;
	}

	g_main_loop_quit(_mainLoop);
	return true;
}

bool BaseFilterGraph::rewind(void) {
	return false;
}

BaseFilterGraph::~BaseFilterGraph(void) {
	if (_mainLoop != NULL) {
		g_main_loop_unref(_mainLoop);
	}
}

}

