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
#include <GLEngine/GLDevice.h>

namespace gstplayer {

	class VideoTrack : public QThread{
		private:
			utils::SmartPtr< gl::GLDevice > _glDevice;
			utils::SmartPtr<multimedia::CGLVideoFilterGraph> _filterGraph;
			std::string _uri;

		public:
			VideoTrack( const std::string& uri, utils::SmartPtr< gl::GLDevice >& glDevice)throw(multimedia::GstException);
			void run();
			virtual ~VideoTrack();
	};

}

#endif /* GSTPLAYER_H_ */
