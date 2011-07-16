TEMPLATE = app
Release:TARGET = release/GstPlayer
Debug:TARGET = debug/GstPlayer
QT += core \
    gui \
    opengl
HEADERS += GstPlayer/VideoTrack.h \
    GstPlayer/GUI/GstPlayerWidget.h \
    ui_gstplayer.h
SOURCES += GstPlayer/VideoTrack.cpp \
    GstPlayer/GUI/GstPlayerWidget.cpp \
    main.cpp
FORMS += gstplayer.ui
RESOURCES += 
INCLUDEPATH += ../GLEngine \
    ../Utilities \
    ../Multimedia \
    /usr/include/gstreamer-0.10 \
    /usr/include/glib-2.0 \
    /usr/include/libxml2 \
    /usr/lib/i386-linux-gnu/glib-2.0/include
LIBS += -lMultimedia \
    -L../GLEngine/Debug \
    -L../Utilities/Debug \
    -L../Multimedia/Debug \
    -lgstreamer-0.10 \
    -lgstvideo-0.10 \
    -lGLEngine \
    -lUtilities
