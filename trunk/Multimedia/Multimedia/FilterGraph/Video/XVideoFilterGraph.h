/*
 * XVideoFilterGraph.h
 *
 *  Created on: Feb 23, 2011
 *      Author: m1cRo
 */

#ifndef XVIDEOFILTERGRAPH_H_
#define XVIDEOFILTERGRAPH_H_

#include <Multimedia/FilterGraph/BasePlaybinFilterGraph.h>
#include <Multimedia/Filter/Sink/Video/XVideoImageSink.h>
#include <Multimedia/Filter/Sink/Audio/StandardAudioSinkFilter.h>

namespace multimedia {

	class XVideoFilterGraph: public multimedia::BasePlaybinFilterGraph {
		private:
			XVideoImageSink _videoSink;
			StandardAudioSinkFilter _audioSink;

		public:
			XVideoFilterGraph(const std::string& fileName)throw(GstException);
			XVideoFilterGraph(const std::string& fileName, gulong xWindowId)throw(GstException);
			virtual ~XVideoFilterGraph();
	};

}

#endif /* XVIDEOFILTERGRAPH_H_ */
