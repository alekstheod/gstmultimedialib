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
#include <GLEngine/Device.h>
#include <Multimedia/Filter/Sink/Video/OpenGL/CGLVideoSinkFilter.h>
#include <Multimedia/Filter/Sink/Audio/StandardAudioSinkFilter.h>

namespace gstplayer {

class VideoTrack: public QThread {
private:
    utils::SharedPtr<gl::Device> _glDevice;
    
    utils::SharedPtr< multimedia::PlaybinFilterGraph< multimedia::CGLVideoSinkFilter, multimedia::StandardAudioSinkFilter> > _filterGraph;
    std::string _uri;
    
protected:
  void run();

public:
    VideoTrack(const std::string& uri, utils::SharedPtr<gl::Device>& glDevice);
    virtual ~VideoTrack();
};

}

#endif /* GSTPLAYER_H_ */
