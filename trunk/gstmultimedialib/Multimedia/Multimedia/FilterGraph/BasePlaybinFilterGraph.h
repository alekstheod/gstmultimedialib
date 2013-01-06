/*
 * BasePlayBinFilterGraph.h
 *
 *  Created on: Jul 3, 2010
 *      Author: m1cro
 */

#ifndef BASEPLAYBINFILTERGRAPH_H_
#define BASEPLAYBINFILTERGRAPH_H_
#include <gst/gst.h>
#include <string>
#include <Multimedia/GstException.h>
#include <Multimedia/Filter/BaseFilter/IFilter.h>
#include <Multimedia/Utilities/GSmartPtr.h>
#include <Multimedia/Filter/BaseFilter/Callback/ABaseVideoCallbackSinkFilter.h>
#include <Multimedia/GstObject.h>

namespace multimedia {

class SourceFilter;
class BaseSinkFilter;
class BaseEncoderFilter;
  
class BasePlaybinFilterGraph: public GstObject {
private:
	GMainLoop* _mainLoop;
	GSmartPtr<GstElement> _pipeline;

public:
	const std::string _fileName;
	static const std::string CONST_PLAYBIN_PLUGIN_NAME;
	static const std::string CONST_PLAYBIN_PLUGIN_DESCRIPTION;

private:
	static gboolean mainLoop(GstBus* bus, GstMessage* msg, gpointer data);

protected:
	bool setAudioSink(BaseSinkFilter* audioSink);
	bool setVideoSink(BaseSinkFilter* videoSink);
	bool setVideoSink(ABaseVideoCallbackSinkFilter* videoSink);
	bool setEncoder(BaseEncoderFilter* encoder);

public:
	BasePlaybinFilterGraph(const std::string& fileName) throw (GstException);
	bool play(void);
	bool stop(void);
	bool rewind(void);
	virtual ~BasePlaybinFilterGraph();
};

}

#endif /* BASEPLAYBINFILTERGRAPH_H_ */
