cmake_minimum_required(VERSION 2.8)
project(GstPlayer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )
SET( CMAKE_CXX_COMPILER clang++ )
ADD_DEFINITIONS(-Wall)
set(-DQT_INCLUDE_DIR /usr/include/qt4)
set(-DQMAKE_EXECUTABLE /usr/bin/qmake-qt4)

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

find_package(Qt4 COMPONENTS QtOpenGL QtCore QtGui REQUIRED )
if (QT_FOUND)
  include(${QT_USE_FILE})
  include_directories(${QT_INCLUDE_DIR})
endif (QT_FOUND)

find_package (GStreamer REQUIRED)
if (GSTREAMER_FOUND)
  include_directories(${PC_GSTREAMER_INCLUDE_DIRS})
endif (GSTREAMER_FOUND)

include_directories(. ../Utilities ../GLEngine ../Multimedia)

file(GLOB_RECURSE GSTPLAYER_SOURCES main.cpp GstPlayer/*.cpp)

add_executable( GstPlayer ${GSTPLAYER_SOURCES})

message("glib2.0 libraries: " ${GLIB2_LIBRARIES})

target_link_libraries(GstPlayer
			pthread
			gobject-2.0 #ubuntu 13.04 fix
			Multimedia
			${OPENGL_LIBRARIES}
			${QT_LIBRARIES}
			${GLIB2_LIBRARIES}
			${GSTREAMER_VIDEO_LIBRARY}
			${GSTREAMER_LIBRARIES}
)