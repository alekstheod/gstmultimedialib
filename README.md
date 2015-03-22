# gstmultimedialib
Automatically exported from code.google.com/p/gstmultimedialib
Wrapper for gstreamer c library. The scope of this library is to provide an object oriented easy to use wrapper library for a gstreamer. One of the key features of this library is a support of the custom c++ based plugins which can modify or present in a special way the multimedia data. One example of those is a custom opengl based video sink.
Simple example

Creating a filter graph and running it.

/// This code will construct a graph of the filters with a custom opengl based sink and a standard audio sink filters.

using namespace multimedia;
PlaybinFilterGraph< CGLVideoSinkFilter, StandardAudioSinkFilter> graph( "v4l2:///dev/video0",
                                                                        CGLVideoSinkFilter ( device ) );


/// In order to start the stream you have to send a play signal.
m_graph.sendSignal ( PlaySignal() );
