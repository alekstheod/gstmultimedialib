/*
 * ADemuxer.h
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#ifndef ADEMUXER_H_
#define ADEMUXER_H_
#include <gst/gst.h>
#include <string>
#include <Multimedia/GstException.h>
#include <Multimedia/Filter/BaseFilter/BaseDecoderFilter.h>
#include <Multimedia/Utilities/GSmartPtr.h>
#include <Multimedia/GstObject.h>

namespace multimedia {

class BaseDemuxerFilter: public IFilter, GstObject {
private:
	GSmartPtr<GstElement> _demuxer;
	GSmartPtr<GstElement> _videoDecoder;
	GSmartPtr<GstElement> _audioDecoder;

private:
	friend class SourceFilter;
	friend class BasePlaybinFilterGraph;

private:
	static void onAddPad(GstElement* element, GstPad* pad, gpointer data);
	void newPad(GstElement* element, GstPad* pad);

public:
	BaseDemuxerFilter(const std::string& pluginName,
			const std::string& description) throw (GstException);
	bool connect(BaseDecoderFilter* decoder);
	bool dynamicConnectVideo(BaseDecoderFilter* videoDecoder);
	bool dynamicConnectAudio(BaseDecoderFilter* audioDecoder);
	bool addToPipeline(GstElement* pipeline);
	virtual ~BaseDemuxerFilter(void);
};

}

#endif /* ADEMUXER_H_ */
