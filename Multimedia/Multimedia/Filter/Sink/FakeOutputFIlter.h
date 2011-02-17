/*
 * FakeOutputFIlter.h
 *
 *  Created on: Jul 4, 2010
 *      Author: m1cro
 */

#ifndef FAKEOUTPUTFILTER_H_
#define FAKEOUTPUTFILTER_H_

#include <Multimedia/Filter/BaseFilter/BaseOutputFilter.h>

namespace multimedia {

	class FakeOutputFIlter: public BaseOutputFilter {
		public:
			static const std::string CONST_PLUGIN_NAME;
			static const std::string CONST_PLUGIN_DESCRIPTION;

		public:
			FakeOutputFIlter();
			virtual ~FakeOutputFIlter();
	};

}

#endif /* FAKEOUTPUTFILTER_H_ */
