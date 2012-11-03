/*
 * GstPlayer.cpp
 *
 *  Created on: Jun 26, 2011
 *      Author: alekstheod
 */

#include "VideoTrack.h"

namespace gstplayer {

VideoTrack::VideoTrack(const std::string& uri,
                       utils::SharedPtr<gl::Device>& glDevice) throw (multimedia::GstException) {
    if (glDevice == NULL ) {
        throw multimedia::GstException(
            "GstPlayer::GstPlayer - Wrong argument glDevice==NULL");
    }

    _uri = uri;
    _glDevice = glDevice;
}

VideoTrack::~VideoTrack() {
    if ( _filterGraph != NULL ) {
        _filterGraph->stop();
        this->wait(1000);
    }
}

void VideoTrack::run() {
    _filterGraph = new multimedia::CGLVideoFilterGraph(_uri, _glDevice);
    _filterGraph->play();
}
}
