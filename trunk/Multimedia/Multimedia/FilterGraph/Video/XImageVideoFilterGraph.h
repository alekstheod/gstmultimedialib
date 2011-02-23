/*
 * XImageVideoFilterGraph.h
 *
 *  Created on: Feb 23, 2011
 *      Author: m1cRo
 */

#ifndef XIMAGEVIDEOFILTERGRAPH_H_
#define XIMAGEVIDEOFILTERGRAPH_H_

#include <Multimedia/FilterGraph/BasePlaybinFilterGraph.h>
#include <Multimedia/Filter/Sink/Video/ImageVideoSink.h>
#include <Multimedia/Filter/Sink/Audio/StandardAudioSinkFilter.h>

namespace multimedia {

	class XImageVideoFilterGraph: public multimedia::BasePlaybinFilterGraph {
		private:
			ImageVideoSink _videoSink;
			StandardAudioSinkFilter _audioSink;

		public:
			XImageVideoFilterGraph(const std::string& fileName);
			virtual ~XImageVideoFilterGraph();
	};

}

#endif /* XIMAGEVIDEOFILTERGRAPH_H_ */
