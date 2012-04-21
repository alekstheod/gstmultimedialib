cmake_minimum_required(VERSION 2.8)
project(Multimedia)

find_package (OpenGL REQUIRED)
if (OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIRS})
endif (OPENGL_FOUND)

find_package (GLUT REQUIRED)
if (GLUT_FOUND)
  include_directories(${GLUT_INCLUDE_DIRS})
endif (GLUT_FOUND)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
find_package (GLIB2 REQUIRED)
if (GLIB2_FOUND)
 message( "Glib-2.0 include dirs : " "${PKG_GLIB_INCLUDE_DIRS}" )
  include_directories(${PKG_GLIB_INCLUDE_DIRS})
endif (GLIB2_FOUND)

find_package (GStreamer REQUIRED)
if (GSTREAMER_FOUND)
  message( "GStreamer include dirs : "  "${PC_GSTREAMER_INCLUDE_DIRS}" )
  include_directories(${PC_GSTREAMER_INCLUDE_DIRS})
endif (GSTREAMER_FOUND)

include_directories(. ../Utilities ../GLEngine)
add_library( Multimedia  STATIC
Multimedia/GstException.cpp
Multimedia/GstObject.cpp
Multimedia/Filter/BaseFilter/Callback/ABaseCallbackSinkFilter.cpp
Multimedia/Filter/BaseFilter/Callback/ABaseVideoCallbackSinkFilter.cpp
Multimedia/Filter/BaseFilter/Callback/gstcallbackplugin.c
Multimedia/Filter/BaseFilter/Callback/gstvideocallbackplugin.c
Multimedia/Filter/BaseFilter/BaseConverterFilter.cpp
Multimedia/Filter/BaseFilter/BaseDecoderFilter.cpp
Multimedia/Filter/BaseFilter/BaseDemuxerFilter.cpp
Multimedia/Filter/BaseFilter/BaseEncoderFilter.cpp
Multimedia/Filter/BaseFilter/BaseSinkFilter.cpp
Multimedia/Filter/BaseFilter/IFilter.cpp
Multimedia/Filter/Intermediate/Audio/AudioConverterFilter.cpp
Multimedia/Filter/Intermediate/Audio/FFMp3DecoderFilter.cpp
Multimedia/Filter/Intermediate/Audio/FFMp3DemuxerFilter.cpp
Multimedia/Filter/Intermediate/FFAviDemuxerFilter.cpp
Multimedia/Filter/Sink/Audio/StandardAudioSinkFilter.cpp
Multimedia/Filter/Sink/Video/OpenGL/VideoFrameModel.cpp
Multimedia/Filter/Sink/Video/OpenGL/CGLVideoSinkFilter.cpp
Multimedia/Filter/Sink/Video/OpenGL/GLVideoSinkFilter.cpp
Multimedia/Filter/Sink/Video/XImageVideoSinkFilter.cpp
Multimedia/Filter/Sink/Video/XVideoImageSink.cpp
Multimedia/Filter/Sink/FakeSinkFilter.cpp
Multimedia/Filter/Sink/SampleGrabberSinkFilter.cpp
Multimedia/Filter/Source/Audio/AlsaSourceFilter.cpp
Multimedia/Filter/Source/SourceFilter.cpp
Multimedia/FilterGraph/Audio/AudioFilterGraph.cpp
Multimedia/FilterGraph/Audio/Mp3FilterGraph.cpp
Multimedia/FilterGraph/Video/CGLVideoFilterGraph.cpp
Multimedia/FilterGraph/Video/GLVideoFilterGraph.cpp
Multimedia/FilterGraph/Video/XImageVideoFilterGraph.cpp
Multimedia/FilterGraph/Video/XVideoFilterGraph.cpp
Multimedia/FilterGraph/BaseFilterGraph.cpp
Multimedia/FilterGraph/BasePlaybinFilterGraph.cpp
Multimedia/FilterGraph/BaseStreamingFilterGraph.cpp)

target_link_libraries(Multimedia
			${PROJECT_SOURCE_DIR}/../build/Utilities/libUtilities.a;
			${PROJECT_SOURCE_DIR}/../build/GLEngine/libGLEngine.a;
			${PROJECT_SOURCE_DIR}/../build/Multimedia/libMultimedia.a;
			${OPENGL_LIBRARIES}
			${GLUT_LIBRARY}
			${QT_LIBRARIES}
			${PKG_GLIB_LIBRARIES}  
			${GSTREAMER_LIBRARIES}
)