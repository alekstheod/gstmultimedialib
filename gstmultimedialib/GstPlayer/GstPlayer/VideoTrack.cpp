/*
 * GstPlayer.cpp
 *
 *  Created on: Jun 26, 2011
 *      Author: alekstheod
 */

#include "VideoTrack.h"

namespace gstplayer
{

VideoTrack::VideoTrack ( const std::string& uri,
                         utils::SharedPtr<gl::Device>& glDevice )
{
    if ( glDevice == NULL ) {
        throw multimedia::GstException (
            "GstPlayer::GstPlayer - Wrong argument glDevice==NULL" );
    }

    m_uri = uri;
    m_glDevice = glDevice;
}

VideoTrack::~VideoTrack()
{
    if ( m_filterGraph != NULL ) {
        m_filterGraph->sendSignal ( multimedia::StopSignal() );
    }

    wait();
}

void VideoTrack::run()
{
    try {
        m_filterGraph = new multimedia::PlaybinFilterGraph<multimedia::CGLVideoSinkFilter,  multimedia::StandardAudioSinkFilter> ( "v4l2:///dev/video0" ,
                multimedia::CGLVideoSinkFilter ( m_glDevice ),
                multimedia::StandardAudioSinkFilter ( "Audio out" ) );

        m_filterGraph->sendSignal ( multimedia::PlaySignal() );
    } catch ( ... ) {
    }
}
}
