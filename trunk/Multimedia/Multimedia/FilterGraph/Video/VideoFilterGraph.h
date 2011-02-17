/*
 * VideoFilterGraph.h
 *
 *  Created on: Jul 24, 2010
 *      Author: m1cRo
 */

#ifndef VIDEOFILTERGRAPH_H_
#define VIDEOFILTERGRAPH_H_

#include <Multimedia/FilterGraph/BasePlaybinFilterGraph.h>
#include <Multimedia/Filter/Sink/Video/GLVideoSink.h>
#include <Multimedia/Filter/Sink/Audio/StandardAudioOutputFilter.h>

namespace multimedia {

	class VideoFilterGraph: public BasePlaybinFilterGraph {
		private:
			GLVideoSink _videoSink;
			StandardAudioOutputFilter _audioSink;

		public:
			VideoFilterGraph(const std::string& filename, const utils::SmartPtr<gl::GLDevice>& glDevice);
			bool RegisterGLVideoSinkStrategy(const utils::SmartPtr<GLVideoSink::IGLVideoSinkStrategy>& strategy);
			virtual ~VideoFilterGraph();
	};

}

#endif /* VIDEOFILTERGRAPH_H_ */
