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
set( BOOST_COMPONENTS_NEEDED filesystem system)
set(BOOST_MIN_VERSION "1.46.0")
find_package(Boost ${BOOST_MIN_VERSION} COMPONENTS ${BOOST_COMPONENTS_NEEDED} REQUIRED)

find_package(DevIL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories(. ../Utilities ${IL_INCLUDE_DIR})
add_library(GLEngine STATIC ${GLENGINE_SOURCES})
target_link_libraries(	GLEngine
		    PUBLIC
		        ${IL_LIBRARIES}
		        ${ILU_LIBRARIES}
		        ${ILUT_LIBRARIES}
		        ${Boost_LIBRARIES}
			Utilities
			assimp
			GL
			GLU
)