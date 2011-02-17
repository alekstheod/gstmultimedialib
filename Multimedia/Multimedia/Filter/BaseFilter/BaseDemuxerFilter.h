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
#include <Multimedia/Exception/GstException.h>
#include <Multimedia/Filter/BaseFilter/BaseDecoderFilter.h>
#include <Multimedia/Utilities/GSmartPtr.h>

namespace multimedia {

	class BaseDemuxerFilter: public IFilter {
		private:
			GSmartPtr<GstElement> _demuxer;
			GSmartPtr<GstElement> _videoDecoder;
			GSmartPtr<GstElement> _audioDecoder;

		private:
			friend class SourceFilter;
			friend class BasePlaybinFilterGraph;

		private:
			static void OnAddPad(GstElement* element, GstPad* pad, gpointer data);
			void NewPad(GstElement* element, GstPad* pad);

		public:
			BaseDemuxerFilter(const std::string& pluginName, const std::string& description) throw (GstException);
			bool Connect(BaseDecoderFilter* decoder);
			bool DynamicConnectVideo(BaseDecoderFilter* videoDecoder);
			bool DynamicConnectAudio(BaseDecoderFilter* audioDecoder);
			bool AddToPipeline(GstElement* pipeline);
			virtual ~BaseDemuxerFilter(void);
	};

}

#endif /* ADEMUXER_H_ */
