/*
 * AudioFilterGraph.h
 *
 *  Created on: Jun 6, 2010
 *      Author: m1cro
 */

#ifndef AUDIOFILTERGRAPH_H_
#define AUDIOFILTERGRAPH_H_
#include <Multimedia/Filter/Sink/Audio/StandardAudioOutputFilter.h>
#include <Multimedia/Filter/Source/SourceFilter.h>
#include <Multimedia/FilterGraph/BasePlaybinFilterGraph.h>
#include <Multimedia/Filter/Sink/FakeOutputFIlter.h>

namespace multimedia {

	class AudioFilterGraph: public BasePlaybinFilterGraph {
		private:
			FakeOutputFIlter _videoOutputFilter;
			StandardAudioOutputFilter _audioOutputFilter;
			SourceFilter _sourceFilter;

		public:
			AudioFilterGraph(const std::string& fileName) throw (GstException);
			virtual ~AudioFilterGraph(void);
	};

}

#endif /* AUDIOFILTERGRAPH_H_ */
