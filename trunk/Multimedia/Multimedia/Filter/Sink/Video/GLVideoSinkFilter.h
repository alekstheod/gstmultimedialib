/*
 * GLVideoSink.h
 *
 *  Created on: Feb 22, 2011
 *      Author: m1cRo
 */

#ifndef GLVIDEOSINK_H_
#define GLVIDEOSINK_H_

#include <Multimedia/Filter/BaseFilter/BaseSinkFilter.h>

namespace multimedia {

	class GLVideoSinkFilter: public BaseSinkFilter {
		public:
			static const std::string CONST_PLUGIN_NAME;

		public:
			GLVideoSinkFilter(const std::string& description);
			virtual ~GLVideoSinkFilter();
	};

}

#endif /* GLVIDEOSINK_H_ */
