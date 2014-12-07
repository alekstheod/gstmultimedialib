/*
 * FakeOutputFIlter.cpp
 *
 *  Created on: Jul 4, 2010
 *      Author: m1cro
 */

#include <Multimedia/Filter/Sink/FakeSinkFilter.h>

namespace multimedia {

const std::string FakeSinkFilter::CONST_PLUGIN_NAME = "fakesink";
const std::string FakeSinkFilter::CONST_PLUGIN_DESCRIPTION = "fakeOutputFilter";

FakeSinkFilter::FakeSinkFilter() :
		BaseSinkFilter(CONST_PLUGIN_NAME, CONST_PLUGIN_DESCRIPTION) {
	// TODO Auto-generated constructor stub

}

FakeSinkFilter::~FakeSinkFilter() {
	// TODO Auto-generated destructor stub
}

}

