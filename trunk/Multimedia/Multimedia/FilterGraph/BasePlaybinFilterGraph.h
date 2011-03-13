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
#include <Multimedia/Exception/GstException.h>
#include <Multimedia/Filter/BaseFilter/IFilter.h>
#include <Multimedia/Utilities/GSmartPtr.h>
#include <Multimedia/Filter/BaseFilter/BaseSinkFilter.h>
#include <Multimedia/Filter/BaseFilter/BaseEncoderFilter.h>

namespace multimedia {

	class BasePlaybinFilterGraph {
		private:
			GMainLoop* _mainLoop;
			GSmartPtr<GstElement> _pipeline;

		public:
			const std::string CONST_FILE_NAME;
			static const std::string CONST_PLAYBIN_PLUGIN_NAME;
			static const std::string CONST_PLAYBIN_PLUGIN_DESCRIPTION;

		private:
			static gboolean MainLoop(GstBus* bus, GstMessage* msg, gpointer data);

		protected:
			bool SetAudioSink(BaseSinkFilter* audioSink);
			bool SetVideoSink(BaseSinkFilter* videoSink);
			bool SetEncoder(BaseEncoderFilter* encoder);

		public:
			BasePlaybinFilterGraph(const std::string& fileName) throw (GstException);
			bool Play(void);
			bool Stop(void);
			bool Rewind(void);
			virtual ~BasePlaybinFilterGraph();
	};

}

#endif /* BASEPLAYBINFILTERGRAPH_H_ */
