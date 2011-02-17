/*
 * AudioConverterFilter.h
 *
 *  Created on: Jun 5, 2010
 *      Author: m1cro
 */

#ifndef AUDIOCONVERTERFILTER_H_
#define AUDIOCONVERTERFILTER_H_

#include <Multimedia/Filter/BaseFilter/BaseConverterFilter.h>

namespace multimedia {

	class AudioConverterFilter: public BaseConverterFilter {
		public:
			static const std::string CONST_PLUGIN_NAME;
			static const std::string CONST_PLUGIN_DESCRIPTION;

		public:
			AudioConverterFilter(void) throw (GstException);
			virtual ~AudioConverterFilter(void);
	};

}

#endif /* AUDIOCONVERTERFILTER_H_ */
