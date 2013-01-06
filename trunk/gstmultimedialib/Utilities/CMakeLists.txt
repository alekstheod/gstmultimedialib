cmake_minimum_required(VERSION 2.8)
project(Utilities)
set(GST_LICENSE "BSD")
include_directories(.)
	    
file(GLOB_RECURSE UTILITIES_SOURCES Utilities/*.cpp)

add_library(Utilities STATIC ${UTILITIES_SOURCES})