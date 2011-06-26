/*
 * CGLVideoFilterGraph.h
 *
 *  Created on: Mar 13, 2011
 *      Author: m1cRo
 */

#ifndef CGLVIDEOFILTERGRAPH_H_
#define CGLVIDEOFILTERGRAPH_H_

#include <Multimedia/FilterGraph/BasePlaybinFilterGraph.h>
#include <Multimedia/Filter/Sink/Video/OpenGL/CGLVideoSinkFilter.h>
#include <GLEngine/GLDevice.h>

namespace multimedia {

	class CGLVideoFilterGraph: public multimedia::BasePlaybinFilterGraph {
		private:
			CGLVideoSinkFilter _videoSink;

		public:
			CGLVideoFilterGraph(const std::string& filename, const utils::SmartPtr<gl::GLDevice>& glDevice);
			virtual ~CGLVideoFilterGraph();
	};

}

#endif /* CGLVIDEOFILTERGRAPH_H_ */
