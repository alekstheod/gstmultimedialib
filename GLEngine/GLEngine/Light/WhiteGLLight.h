/*
 * WhiteGLLight.h
 *
 *  Created on: May 20, 2011
 *      Author: m1cRo
 */

#ifndef WHITEGLLIGHT_H_
#define WHITEGLLIGHT_H_

#include "IGLLight.h"

namespace gl {

	class WhiteGLLight: public gl::IGLLight {
		public:
			WhiteGLLight();
			bool applyLight();
			virtual ~WhiteGLLight();
	};

}

#endif /* WHITEGLLIGHT_H_ */
