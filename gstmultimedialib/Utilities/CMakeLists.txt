cmake_minimum_required(VERSION 2.8)
project(Utilities)
set(GST_LICENSE "BSD")
include_directories(.)

add_library(Utilities STATIC
	    Utilities/AException.cpp
	    Utilities/AutoLock/OS_Specific/LMutex.cpp
	    Utilities/AutoLock/OS_Specific/WinMutex.cpp
	    Utilities/AutoLock/LockException.cpp)