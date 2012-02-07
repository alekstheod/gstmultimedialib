/*
 * GStreamer
 * Copyright (C) 2005 Thomas Vander Stichele <thomas@apestaart.org>
 * Copyright (C) 2005 Ronald S. Bultje <rbultje@ronald.bitfreak.net>
 * Copyright (C) 2011 Alex Theodoridis <alekstheod@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Alternatively, the contents of this file may be used under the
 * GNU Lesser General Public License Version 2.1 (the "LGPL"), in
 * which case the following provisions apply instead of the ones
 * mentioned above:
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
/**
 * SECTION:element-callbackplugin
 *
 * FIXME:Describe callbackplugin here.
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <Multimedia/Filter/BaseFilter/Callback/gstvideocallbackplugin.h>
#include <gst/video/video.h>

GST_DEBUG_CATEGORY_STATIC( gst_callback_callbackplugin_debug);
#define GST_CAT_DEFAULT gst_callback_callbackplugin_debug

/* Filter signals and args */
enum {
	/* FILL ME */
	LAST_SIGNAL
};

enum {
	PROP_0, PROP_CALLBACK, PROP_SETCAPS, PROP_ARG
};

/*
 * the capabilities of the inputs and outputs.
 * describe the real formats here.
 */
#ifdef GL_YCBCR_MESA
#define YUV_CAPS ";" GST_VIDEO_CAPS_YUV ("{ UYVY, YUY2 }")
#else
#define YUV_CAPS
#endif
static GstStaticPadTemplate sink_factory = GST_STATIC_PAD_TEMPLATE ("sink",
		GST_PAD_SINK,
		GST_PAD_ALWAYS,
		GST_STATIC_CAPS (GST_VIDEO_CAPS_RGBx ";" GST_VIDEO_CAPS_BGRx YUV_CAPS)
);

GST_BOILERPLATE(GstCallbackVideoCallbackPlugin,
		gst_callback_videocallbackplugin, GstVideoSink, GST_TYPE_VIDEO_SINK);

static void gst_callback_callbackplugin_set_property(GObject * object,
		guint prop_id, const GValue * value, GParamSpec * pspec);
static void gst_callback_callbackplugin_get_property(GObject * object,
		guint prop_id, GValue * value, GParamSpec * pspec);
static gboolean gst_callback_callbackplugin_set_caps(GstPad * pad,
		GstCaps * caps);
static GstFlowReturn gst_callback_callbackplugin_render(GstBaseSink* sink,
		GstBuffer* buf);

/* GObject vmethod implementations */
static void gst_callback_videocallbackplugin_base_init(gpointer gclass) {
	GstElementClass *element_class = GST_ELEMENT_CLASS(gclass);
	gst_element_class_set_details_simple(element_class, "CallbackPlugin",
			"CallbackSinkPlugin", "CallbackSinkPlugin",
			"Alex Theodoridis <alekstheod@gmail.com>");
	gst_element_class_add_pad_template(element_class,
			gst_static_pad_template_get(&sink_factory));
}

/* chain function
 * this function does the actual processing
 */
static GstFlowReturn gst_callback_callbackplugin_render(GstBaseSink* sink,
		GstBuffer* buf) {
	GstCallbackVideoCallbackPlugin *filter =
			(GstCallbackVideoCallbackPlugin*) sink;
	GstFlowReturn result = GST_FLOW_OK;
	if (filter->render_callback != NULL) {
		filter->render_callback(sink, buf, filter->arg);
	}

	return result;
}

/* initialize the callbackplugin's class */
static void gst_callback_videocallbackplugin_class_init(
		GstCallbackVideoCallbackPluginClass * klass) {
	GObjectClass *gobject_class;
	GstElementClass *gstelement_class;
	gobject_class = (GObjectClass *) klass;
	gstelement_class = (GstElementClass *) klass;
	gobject_class->set_property = gst_callback_callbackplugin_set_property;
	gobject_class->get_property = gst_callback_callbackplugin_get_property;
	g_object_class_install_property(
			gobject_class,
			PROP_CALLBACK,
			g_param_spec_pointer(render_video_callback_property,
					"CallbackFunction", "Callback function pointer",
					G_PARAM_READWRITE));
	g_object_class_install_property(
			gobject_class,
			PROP_SETCAPS,
			g_param_spec_pointer(setcaps_video_callback_property,
					"SetCapsCallbackFunction",
					"Callback function pointer for setcaps",
					G_PARAM_READWRITE));
	g_object_class_install_property(
			gobject_class,
			PROP_ARG,
			g_param_spec_pointer(chain_video_callback_arg_property,
					"CallbackArgument", "Callback argument pointer",
					G_PARAM_READWRITE));
	klass->parent_class.parent_class.render =
			gst_callback_callbackplugin_render;
}

/*
 * initialize the new element
 * instantiate pads and add them to element
 * set pad callback functions
 * initialize instance structure
 */
static void gst_callback_videocallbackplugin_init(
		GstCallbackVideoCallbackPlugin * filter,
		GstCallbackVideoCallbackPluginClass * gclass) {
	//filter->element.element.sinkpad = gst_pad_new_from_static_template(&sink_factory, "videosink");
	gst_pad_set_setcaps_function(filter->element.element.sinkpad,
			GST_DEBUG_FUNCPTR(gst_callback_callbackplugin_set_caps));
	gst_pad_set_getcaps_function(filter->element.element.sinkpad,
			GST_DEBUG_FUNCPTR(gst_pad_proxy_getcaps));
	filter->render_callback = NULL;
	filter->setcaps_callback = NULL;
	filter->arg = NULL;
}

static void gst_callback_callbackplugin_set_property(GObject * object,
		guint prop_id, const GValue * value, GParamSpec * pspec) {
	GstCallbackVideoCallbackPlugin *filter = GST_VIDEO_CALLBACKPLUGIN (object);
	switch (prop_id) {
	case PROP_CALLBACK: {
		filter->render_callback = g_value_get_pointer(value);
	}
		break;

	case PROP_SETCAPS: {
		filter->setcaps_callback = g_value_get_pointer(value);
	}
		break;

	case PROP_ARG: {
		filter->arg = g_value_get_pointer(value);
	}
		break;

	default: {
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
	}
		break;
	}
}

static void gst_callback_callbackplugin_get_property(GObject * object,
		guint prop_id, GValue * value, GParamSpec * pspec) {
	GstCallbackVideoCallbackPlugin *filter = GST_VIDEO_CALLBACKPLUGIN (object);
	switch (prop_id) {
	case PROP_CALLBACK: {
		g_value_set_pointer(value, filter->render_callback);
	}
		break;

	case PROP_SETCAPS: {
		g_value_set_pointer(value, filter->setcaps_callback);
	}
		break;

	case PROP_ARG: {
		g_value_set_pointer(value, filter->arg);
	}
		break;

	default: {
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
	}
		break;
	}
}

/* GstElement vmethod implementations */
/* this function handles the link with other elements */
static gboolean gst_callback_callbackplugin_set_caps(GstPad * pad,
		GstCaps * caps) {
	GstCallbackVideoCallbackPlugin *filter;
	filter = GST_VIDEO_CALLBACKPLUGIN (gst_pad_get_parent (pad));
	gboolean result = TRUE;
	if (filter->setcaps_callback != NULL) {
		result = filter->setcaps_callback(pad, caps, filter->arg);
	}

	return result;
}

/* entry point to initialize the plug-in
 * initialize the plug-in itself
 * register the element factories and other features
 */
static gboolean callbackplugin_init(GstPlugin * callbackplugin) {
	GST_DEBUG_CATEGORY_INIT(gst_callback_callbackplugin_debug,
			"videocallbackplugin", 0, "Template callbackplugin");
	return gst_element_register(callbackplugin, "videocallbackplugin",
			GST_RANK_NONE, GST_TYPE_VIDEO_CALLBACKPLUGIN);
}

/* PACKAGE: this is usually set by autotools depending on some _INIT macro
 * in configure.ac and then written into and defined in config.h, but we can
 * just set it ourselves here in case someone doesn't use autotools to
 * compile this code. GST_PLUGIN_DEFINE needs PACKAGE to be defined.
 */
#ifndef PACKAGE
#define PACKAGE "callbackplugin"
#endif
/*
 * gstreamer looks for this structure to register callbackplugins
 */GST_PLUGIN_DEFINE (
		GST_VERSION_MAJOR,
		GST_VERSION_MINOR,
		"videocallbackplugin",
		"CallBack plugin",
		callbackplugin_init,
		"0.10.0",
		"BSD",
		"GStreamer",
		"http://gstreamer.net/"
)
