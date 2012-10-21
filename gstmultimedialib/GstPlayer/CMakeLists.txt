cmake_minimum_required(VERSION 2.8)
project(GstPlayer)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../Multimedia/cmake")

find_package (GLIB2 REQUIRED)
if (GLIB2_FOUND)
  include_directories(${PKG_GLIB_INCLUDE_DIRS})
endif (GLIB2_FOUND)

find_package (OpenGL REQUIRED)
if (OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIRS})
endif (OPENGL_FOUND)

find_package (GLUT REQUIRED)
#if (GLUT_FOUND)
  include_directories(${GLUT_INCLUDE_DIRS})
#endif (GLUT_FOUND)

find_package(Qt4 4.6.2 COMPONENTS QtOpenGL QtCore QtGui REQUIRED )
if (QT_FOUND)
  include(${QT_USE_FILE})
  include_directories(${QT_INCLUDE_DIR})
endif (QT_FOUND)

find_package (GStreamer REQUIRED)
if (GSTREAMER_FOUND)
  include_directories(${PC_GSTREAMER_INCLUDE_DIRS})
endif (GSTREAMER_FOUND)

include_directories(. ../Utilities ../GLEngine ../Multimedia)

add_executable( GstPlayer main.cpp 
GstPlayer/VideoTrack.cpp
GstPlayer/GUI/GstPlayerWidget.cpp
GstPlayer/GUI/Menu/MenuModel.cpp
GstPlayer/GUI/Menu/PlayButton/APlayButtonState.cpp
GstPlayer/GUI/Menu/PlayButton/State/PausedPlayButtonState.cpp
GstPlayer/GUI/Menu/PlayButton/State/PlayingPlayButtonState.cpp
)

target_link_libraries(GstPlayer
			${PROJECT_SOURCE_DIR}/../build/Multimedia/libMultimedia.a;
			${PROJECT_SOURCE_DIR}/../build/GLEngine/libGLEngine.a;
			${PROJECT_SOURCE_DIR}/../build/Utilities/libUtilities.a;
			${OPENGL_LIBRARIES}
			${QT_LIBRARIES}
			${PKG_GLIB_LIBRARIES}  
			${GSTREAMER_VIDEO_LIBRARY}
			${GSTREAMER_LIBRARIES}
)