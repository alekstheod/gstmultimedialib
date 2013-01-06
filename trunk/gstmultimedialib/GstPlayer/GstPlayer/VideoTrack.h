/*
 * GstPlayer.h
 *
 *  Created on: Jun 26, 2011
 *      Author: alekstheod
 */

#ifndef GSTPLAYER_H_
#define GSTPLAYER_H_
#include <qthread.h>
#include <Multimedia/FilterGraph/Video/CGLVideoFilterGraph.h>
#include <GLEngine/Device.h>

namespace gstplayer {

class VideoTrack: public QThread {
private:
    utils::SharedPtr<gl::Device> _glDevice;
    utils::SharedPtr<multimedia::CGLVideoFilterGraph> _filterGraph;
    std::string _uri;
    
protected:
  void run();

public:
    VideoTrack(const std::string& uri, utils::SharedPtr<gl::Device>& glDevice);
    virtual ~VideoTrack();
};

}

#endif /* GSTPLAYER_H_ */
