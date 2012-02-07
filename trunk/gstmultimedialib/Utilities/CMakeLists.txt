project(Utilities)
cmake_minimum_required(VERSION 2.8)

include_directories(.)

add_library(Utilities
	    Utilities/AException.cpp
	    Utilities/AutoLock/LLockObject.cpp
	    Utilities/AutoLock/WinLockObject.cpp
	    Utilities/AutoLock/LockException.cpp 
	    Utilities/AutoLock/AutoLock.cpp
	    Utilities/StrUtil/StrUtil.cpp)
