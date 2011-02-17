/*
 * FakeOutputFIlter.cpp
 *
 *  Created on: Jul 4, 2010
 *      Author: m1cro
 */

#include <Multimedia/Filter/Sink/FakeOutputFIlter.h>

namespace multimedia {

	const std::string FakeOutputFIlter::CONST_PLUGIN_NAME = "fakesink";
	const std::string FakeOutputFIlter::CONST_PLUGIN_DESCRIPTION = "fakeOutputFilter";

	FakeOutputFIlter::FakeOutputFIlter() :
		BaseOutputFilter(CONST_PLUGIN_NAME, CONST_PLUGIN_DESCRIPTION) {
		// TODO Auto-generated constructor stub

	}

	FakeOutputFIlter::~FakeOutputFIlter() {
		// TODO Auto-generated destructor stub
	}

}

