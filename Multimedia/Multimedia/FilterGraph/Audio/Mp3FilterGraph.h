/*
 * Mp3FilterGraph.h
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#ifndef MP3FILTERGRAPH_H_
#define MP3FILTERGRAPH_H_
#include <gst/gst.h>
#include <Multimedia/Filter/Source/SourceFilter.h>
#include <Multimedia/Filter/Intermediate/Audio/FFMp3DecoderFilter.h>
#include <Multimedia/Filter/Intermediate/Audio/FFMp3DemuxerFilter.h>
#include <Multimedia/Filter/Intermediate/Audio/AudioConverterFilter.h>
#include <Multimedia/Filter/Sink/Audio/StandardAudioSinkFilter.h>
#include <Multimedia/FilterGraph/BaseFilterGraph.h>

namespace multimedia {

class Mp3FilterGraph: public BaseFilterGraph {
private:
	SourceFilter _src;
	FFMp3DemuxerFilter _demuxer;
	FFMp3DecoderFilter _decoder;
	AudioConverterFilter _converter;
	StandardAudioSinkFilter _audioOutput;

public:
	Mp3FilterGraph(const std::string& sourceFileName) throw (GstException);
	virtual ~Mp3FilterGraph(void);
};

}

#endif /* MP3FILTERGRAPH_H_ */
