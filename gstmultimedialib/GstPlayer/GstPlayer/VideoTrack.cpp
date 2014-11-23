/*
 * GstPlayer.cpp
 *
 *  Created on: Jun 26, 2011
 *      Author: alekstheod
 */

#include "VideoTrack.h"

namespace gstplayer
{

VideoTrack::VideoTrack ( const std::string& uri, gl::Scene& glDevice ):m_glDevice(glDevice),
									m_filterGraph(uri ,
										      multimedia::CGLVideoSinkFilter ( m_glDevice ),
										      multimedia::StandardAudioSinkFilter ( "Audio out" )) {}

VideoTrack::~VideoTrack()
{
    m_filterGraph.sendSignal ( multimedia::StopSignal() );
    wait();
}

void VideoTrack::run()
{
    try {
        m_filterGraph.sendSignal ( multimedia::PlaySignal() );
    } catch ( ... ) {
    }
}
}
