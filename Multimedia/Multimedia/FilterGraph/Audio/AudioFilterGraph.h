/*
 * AudioFilterGraph.h
 *
 *  Created on: Jun 6, 2010
 *      Author: m1cro
 */

#ifndef AUDIOFILTERGRAPH_H_
#define AUDIOFILTERGRAPH_H_
#include <Multimedia/Filter/Sink/Audio/StandardAudioSinkFilter.h>
#include <Multimedia/Filter/Source/SourceFilter.h>
#include <Multimedia/FilterGraph/BasePlaybinFilterGraph.h>
#include <Multimedia/Filter/Sink/FakeSinkFilter.h>

namespace multimedia {

class AudioFilterGraph: public BasePlaybinFilterGraph {
private:
	FakeSinkFilter _videoOutputFilter;
	SourceFilter _sourceFilter;
	StandardAudioSinkFilter _audioSink;

public:
	AudioFilterGraph(const std::string& fileName) throw (GstException);
	virtual ~AudioFilterGraph(void);
};

}

#endif /* AUDIOFILTERGRAPH_H_ */
