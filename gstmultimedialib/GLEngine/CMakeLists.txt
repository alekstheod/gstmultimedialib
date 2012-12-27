cmake_minimum_required(VERSION 2.8)
project(GLEngine)

find_package (OpenGL REQUIRED)
if (OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIRS})
endif (OPENGL_FOUND)

find_package (GLUT REQUIRED)
if (GLUT_FOUND)
  include_directories(${GLUT_INCLUDE_DIRS})
endif (GLUT_FOUND)

include_directories(. ../Utilities)

file(GLOB_RECURSE GLENGINE_SOURCES GLEngine/*.cpp)

add_library(GLEngine STATIC ${GLENGINE_SOURCES})
