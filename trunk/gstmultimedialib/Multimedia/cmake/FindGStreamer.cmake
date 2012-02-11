# - Try to find GStreamer
# Once done this will define
#
#  GSTREAMER_FOUND - system has GStreamer
#  GSTREAMER_INCLUDE_DIR - the GStreamer include directory
#  GSTREAMER_LIBRARIES - the libraries needed to use GStreamer
#  GSTREAMER_DEFINITIONS - Compiler switches required for using GStreamer

# Copyright (c) 2006, Tim Beaulen <tbscope@gmail.com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

# TODO: Other versions --> GSTREAMER_X_Y_FOUND (Example: GSTREAMER_0_8_FOUND and GSTREAMER_0_10_FOUND etc)

IF (GSTREAMER_INCLUDE_DIR AND GSTREAMER_LIBRARIES AND GSTREAMER_BASE_LIBRARY AND GSTREAMER_INTERFACE_LIBRARY AND GSTREAMER_VIDEO_LIBRARY)
   # in cache already
   SET(GStreamer_FIND_QUIETLY TRUE)
ELSE (GSTREAMER_INCLUDE_DIR AND GSTREAMER_LIBRARIES AND GSTREAMER_BASE_LIBRARY AND GSTREAMER_INTERFACE_LIBRARY AND GSTREAMER_VIDEO_LIBRARY)
   SET(GStreamer_FIND_QUIETLY FALSE)
ENDIF (GSTREAMER_INCLUDE_DIR AND GSTREAMER_LIBRARIES AND GSTREAMER_BASE_LIBRARY AND GSTREAMER_INTERFACE_LIBRARY AND GSTREAMER_VIDEO_LIBRARY)

IF (NOT WIN32)
   # use pkg-config to get the directories and then use these values
   # in the FIND_PATH() and FIND_LIBRARY() calls
   FIND_PACKAGE(PkgConfig)
   PKG_CHECK_MODULES(PC_GSTREAMER QUIET gstreamer-0.10)
   #MESSAGE(STATUS "DEBUG: GStreamer include directory = ${GSTREAMER_INCLUDE_DIRS}")
   #MESSAGE(STATUS "DEBUG: GStreamer link directory = ${GSTREAMER_LIBRARY_DIRS}")
   #MESSAGE(STATUS "DEBUG: GStreamer CFlags = ${GSTREAMER_CFLAGS_OTHER}") 
   SET(GSTREAMER_DEFINITIONS ${PC_GSTREAMER_CFLAGS_OTHER})
ENDIF (NOT WIN32)

FIND_PATH(GSTREAMER_INCLUDE_DIR gst/gst.h
   PATHS
   ${PC_GSTREAMER_INCLUDEDIR}
   ${PC_GSTREAMER_INCLUDE_DIRS}
   #PATH_SUFFIXES gst
   )

FIND_LIBRARY(GSTREAMER_LIBRARIES NAMES gstreamer-0.10
   PATHS
   ${PC_GSTREAMER_LIBDIR}
   ${PC_GSTREAMER_LIBRARY_DIRS}
   )

FIND_LIBRARY(GSTREAMER_BASE_LIBRARY NAMES gstbase-0.10
   PATHS
   ${PC_GSTREAMER_LIBDIR}
   ${PC_GSTREAMER_LIBRARY_DIRS}
   )

FIND_LIBRARY(GSTREAMER_INTERFACE_LIBRARY NAMES gstinterfaces-0.10
   PATHS
   ${PC_GSTREAMER_LIBDIR}
   ${PC_GSTREAMER_LIBRARY_DIRS}
   )

FIND_LIBRARY(GSTREAMER_VIDEO_LIBRARY NAMES gstvideo-0.10
   PATHS
   ${PC_GSTREAMER_LIBDIR}
   ${PC_GSTREAMER_LIBRARY_DIRS}
   )

IF (GSTREAMER_INCLUDE_DIR)
   #MESSAGE(STATUS "DEBUG: Found GStreamer include dir: ${GSTREAMER_INCLUDE_DIR}")
ELSE (GSTREAMER_INCLUDE_DIR)
   MESSAGE(STATUS "GStreamer: WARNING: include dir not found")
ENDIF (GSTREAMER_INCLUDE_DIR)

IF (GSTREAMER_LIBRARIES)
   #MESSAGE(STATUS "DEBUG: Found GStreamer library: ${GSTREAMER_LIBRARIES}")
ELSE (GSTREAMER_LIBRARIES)
   MESSAGE(STATUS "GStreamer: WARNING: library not found")
ENDIF (GSTREAMER_LIBRARIES)

IF (GSTREAMER_VIDEO_LIBRARY)
   #MESSAGE(STATUS "DEBUG: Found GStreamer-video library: ${GSTREAMER_VIDEO_LIBRARY}")
ELSE (GSTREAMER_VIDEO_LIBRARY)
   MESSAGE(STATUS "GStreamer: WARNING: video library not found")
ENDIF (GSTREAMER_VIDEO_LIBRARY)

IF (GSTREAMER_INTERFACE_LIBRARY)
   #MESSAGE(STATUS "DEBUG: Found GStreamer interface library: ${GSTREAMER_INTERFACE_LIBRARY}")
ELSE (GSTREAMER_INTERFACE_LIBRARY)
   MESSAGE(STATUS "GStreamer: WARNING: interface library not found")
ENDIF (GSTREAMER_INTERFACE_LIBRARY)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GStreamer  DEFAULT_MSG  GSTREAMER_LIBRARIES GSTREAMER_INCLUDE_DIR GSTREAMER_BASE_LIBRARY GSTREAMER_INTERFACE_LIBRARY GSTREAMER_VIDEO_LIBRARY)

MARK_AS_ADVANCED(GSTREAMER_INCLUDE_DIR GSTREAMER_LIBRARIES GSTREAMER_BASE_LIBRARY GSTREAMER_INTERFACE_LIBRARY GSTREAMER_VIDEO_LIBRARY)