/*
 * BaseFilterGraph.h
 *
 *  Created on: Jun 6, 2010
 *      Author: m1cro
 */

#ifndef BASEFILTERGRAPH_H_
#define BASEFILTERGRAPH_H_
#include <gst/gst.h>
#include <string>
#include <Multimedia/Exception/GstException.h>
#include <Multimedia/Filter/BaseFilter/IFilter.h>
#include <Multimedia/Utilities/GSmartPtr.h>

namespace multimedia {

	class BaseFilterGraph {
		private:
			GMainLoop* _mainLoop;
			GSmartPtr<GstElement> _pipeline;

		private:
			static gboolean MainLoop(GstBus *bus, GstMessage *msg, gpointer data);

		protected:
			bool addFilter(IFilter* filter);

		public:
			BaseFilterGraph(const std::string& graphName) throw (GstException);
			bool play(void);
			bool stop(void);
			bool rewind(void);
			virtual ~BaseFilterGraph(void);
	};

}

#endif /* BASEFILTERGRAPH_H_ */
