/*
 * GstPlayer.h
 *
 *  Created on: Jun 26, 2011
 *      Author: alekstheod
 */

#ifndef GSTPLAYER_H_
#define GSTPLAYER_H_
#include <qthread.h>
#include <Multimedia/FilterGraph/PlaybinFilterGraph.h>
#include <GLEngine/Scene.h>
#include <Multimedia/Filter/Sink/Video/OpenGL/CGLVideoSinkFilter.h>
#include <Multimedia/Filter/Sink/Audio/StandardAudioSinkFilter.h>

namespace gstplayer {

class VideoTrack: public QThread {
private:
    /// @brief Rendering device.
    gl::Scene& m_glDevice;
    
    /// @brief the pipeline
    multimedia::PlaybinFilterGraph< multimedia::CGLVideoSinkFilter, multimedia::StandardAudioSinkFilter> m_filterGraph;
    
private:
  void run();

public:
    VideoTrack(const std::string& uri, gl::Scene& glDevice);
    virtual ~VideoTrack();
};

}

#endif /* GSTPLAYER_H_ */
