/*
 * GstPlayer.cpp
 *
 *  Created on: Jun 26, 2011
 *      Author: alekstheod
 */

#include "VideoTrack.h"

namespace gstplayer {

VideoTrack::VideoTrack(const std::string& uri,
                       utils::SharedPtr<gl::Device>& glDevice) {
    if (glDevice == NULL ) {
        throw multimedia::GstException(
            "GstPlayer::GstPlayer - Wrong argument glDevice==NULL");
    }

    _uri = uri;
    _glDevice = glDevice;
}

VideoTrack::~VideoTrack() {
    if ( _filterGraph != NULL ) {
        _filterGraph->sendSignal( multimedia::StopSignal() );
    }
    
    wait();
}

void VideoTrack::run() {
  try{
    _filterGraph = new multimedia::PlaybinFilterGraph<multimedia::CGLVideoSinkFilter,  multimedia::StandardAudioSinkFilter>( "v4l2:///dev/video0" , multimedia::CGLVideoSinkFilter(_glDevice), multimedia::StandardAudioSinkFilter("Audio out") );
    _filterGraph->sendSignal( multimedia::PlaySignal() );
  }catch(...){
  }
}
}
