/*
 * WhiteGLLight.h
 *
 *  Created on: May 20, 2011
 *      Author: m1cRo
 */

#ifndef WHITEGLLIGHT_H_
#define WHITEGLLIGHT_H_

#include "ILight.h"

namespace gl {

class WhiteLight: public gl::ILight {
public:
	WhiteLight();
	bool applyLight();
	virtual ~WhiteLight();
};

}

#endif /* WHITEGLLIGHT_H_ */
