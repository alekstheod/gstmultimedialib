cmake_minimum_required(VERSION 2.8)
project(Utilities)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )
SET( CMAKE_CXX_COMPILER clang++ )
set(GST_LICENSE "BSD")
include_directories(.)
	    
file(GLOB_RECURSE UTILITIES_SOURCES Utilities/MPL/Tuple.cpp Utilities/*.cpp)

add_library(Utilities STATIC ${UTILITIES_SOURCES} )