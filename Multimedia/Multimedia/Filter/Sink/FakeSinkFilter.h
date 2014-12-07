/*
 * FakeOutputFIlter.h
 *
 *  Created on: Jul 4, 2010
 *      Author: m1cro
 */

#ifndef FAKEOUTPUTFILTER_H_
#define FAKEOUTPUTFILTER_H_

#include <Multimedia/Filter/BaseFilter/BaseSinkFilter.h>

namespace multimedia {

class FakeSinkFilter: public BaseSinkFilter {
public:
	static const std::string CONST_PLUGIN_NAME;
	static const std::string CONST_PLUGIN_DESCRIPTION;

public:
	FakeSinkFilter();
	virtual ~FakeSinkFilter();
};

}

#endif /* FAKEOUTPUTFILTER_H_ */
