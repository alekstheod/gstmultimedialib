/*
 * VideoFilterGraph.h
 *
 *  Created on: Jul 24, 2010
 *      Author: m1cRo
 */

#ifndef VIDEOFILTERGRAPH_H_
#define VIDEOFILTERGRAPH_H_

#include <Multimedia/FilterGraph/BasePlaybinFilterGraph.h>
#include <Multimedia/Filter/Sink/Video/CGLVideoSink.h>
#include <Multimedia/Filter/Sink/Audio/StandardAudioSinkFilter.h>

namespace multimedia {

	class GLVideoFilterGraph: public BasePlaybinFilterGraph {
		private:
			CGLVideoSink _videoSink;
			StandardAudioSinkFilter _audioSink;

		public:
			GLVideoFilterGraph(const std::string& filename, const utils::SmartPtr<gl::GLDevice>& glDevice);
			bool RegisterGLVideoSinkStrategy(const utils::SmartPtr<CGLVideoSink::IGLVideoSinkStrategy>& strategy);
			virtual ~GLVideoFilterGraph();
	};

}

#endif /* VIDEOFILTERGRAPH_H_ */
