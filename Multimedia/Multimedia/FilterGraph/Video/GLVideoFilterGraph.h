/*
 * VideoFilterGraph.h
 *
 *  Created on: Jul 24, 2010
 *      Author: m1cRo
 */

#ifndef VIDEOFILTERGRAPH_H_
#define VIDEOFILTERGRAPH_H_

#include <Multimedia/FilterGraph/BasePlaybinFilterGraph.h>
#include <Multimedia/Filter/Sink/Video/CGLVideoSinkFilter.h>
#include <Multimedia/Filter/Sink/Audio/StandardAudioSinkFilter.h>

namespace multimedia {

	class GLVideoFilterGraph: public BasePlaybinFilterGraph {
		private:
			CGLVideoSinkFilter _videoSink;
			StandardAudioSinkFilter _audioSink;

		public:
			GLVideoFilterGraph(const std::string& filename, const utils::SmartPtr<gl::GLDevice>& glDevice);
			bool registerGLVideoSinkStrategy(const utils::SmartPtr<CGLVideoSinkFilter::IGLVideoSinkStrategy>& strategy);
			virtual ~GLVideoFilterGraph();
	};

}

#endif /* VIDEOFILTERGRAPH_H_ */
