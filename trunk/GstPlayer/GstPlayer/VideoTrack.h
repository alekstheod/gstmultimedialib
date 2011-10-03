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

	class VideoTrack : public QThread{
		private:
			utils::SmartPtr< gl::Device > _glDevice;
			utils::SmartPtr<multimedia::CGLVideoFilterGraph> _filterGraph;
			std::string _uri;

		public:
			VideoTrack( const std::string& uri, utils::SmartPtr< gl::Device >& glDevice)throw(multimedia::GstException);
			void run();
			virtual ~VideoTrack();
	};

}

#endif /* GSTPLAYER_H_ */
