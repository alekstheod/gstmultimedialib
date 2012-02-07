project(Multimedia)
cmake_minimum_required(VERSION 2.8)

find_package (OpenGL REQUIRED)
if (OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIRS})
endif (OPENGL_FOUND)

find_package (GLUT REQUIRED)
if (GLUT_FOUND)
  include_directories(${GLUT_INCLUDE_DIRS})
endif (GLUT_FOUND)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package (GLIB2 REQUIRED)
if (GLIB2_FOUND)
  include_directories(${GLIB2_INCLUDE_DIRS})
endif (GLIB2_FOUND)