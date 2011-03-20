/*
 * IFilter.h
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#ifndef IFILTER_H_
#define IFILTER_H_
#include <gst/gst.h>

namespace multimedia {

	class IFilter {
		public:
			IFilter(void);
			virtual bool addToPipeline(GstElement* pipeline) = 0;
			virtual ~IFilter(void);
	};

}

#endif /* IFILTER_H_ */
