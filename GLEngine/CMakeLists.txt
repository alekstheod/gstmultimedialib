cmake_minimum_required(VERSION 2.8)
project(GLEngine)

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

file(GLOB_RECURSE GLENGINE_SOURCES GLEngine/Model/AssimpModel.cpp GLEngine/*.cpp GLEngine/Model/Model.cpp)

include_directories(. ../Utilities)
add_library(GLEngine STATIC ${GLENGINE_SOURCES})
target_link_libraries(	GLEngine
		    PUBLIC
			Utilities
			assimp
			GL
			GLU
)