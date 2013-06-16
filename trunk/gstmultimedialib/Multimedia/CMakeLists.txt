cmake_minimum_required(VERSION 2.8)
project(Multimedia)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )
SET( CMAKE_CXX_COMPILER clang++ )
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

file(GLOB_RECURSE MULTIMEDIA_SOURCES Multimedia/*.cpp)
file(GLOB_RECURSE MULTIMEDIA_C_SOURCES Multimedia/FilterGraph/IPlaybin.cpp Multimedia/FilterGraph/IPlaybinListener.cpp Multimedia/*.c)

add_library(Multimedia STATIC ${MULTIMEDIA_SOURCES} ${MULTIMEDIA_C_SOURCES})

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