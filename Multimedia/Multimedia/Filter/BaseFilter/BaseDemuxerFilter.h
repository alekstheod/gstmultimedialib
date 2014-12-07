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

class BaseDemuxerFilter: public AFilter, GstObject {
private:
	GSmartPtr<GstElement> m_demuxer;
	GSmartPtr<GstElement> m_videoDecoder;
	GSmartPtr<GstElement> m_audioDecoder;

private:
	friend class SourceFilter;
	
	template<typename... FilterTypes>
	friend class BasePlaybinFilterGraph;

private:
	static void onAddPad(GstElement* element, GstPad* pad, gpointer data);
	void newPad(GstElement* element, GstPad* pad);

	bool addToPipelineImpl(GstElement* pipeline);
public:
	BaseDemuxerFilter(const std::string& pluginName,
			const std::string& description) throw (GstException);
	bool connect(BaseDecoderFilter* decoder);
	bool dynamicConnectVideo(BaseDecoderFilter* videoDecoder);
	bool dynamicConnectAudio(BaseDecoderFilter* audioDecoder);
	virtual ~BaseDemuxerFilter(void);
};

}

#endif /* ADEMUXER_H_ */
