/*
 * GstException.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#include "GstException.h"

namespace multimedia {

	GstException::GstException(const std::string& message) : utils::AException(message) {
		// TODO Auto-generated constructor stub

	}

	GstException::~GstException() throw () {
		// TODO Auto-generated destructor stub
	}

}

