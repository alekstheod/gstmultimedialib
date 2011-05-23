/*
 * IGLLight.h
 *
 *  Created on: May 20, 2011
 *      Author: m1cRo
 */

#ifndef IGLLIGHT_H_
#define IGLLIGHT_H_

namespace gl {

	class IGLLight {
		public:
			IGLLight();
			virtual bool applyLight()=0;
			virtual ~IGLLight();
	};

}

#endif /* IGLLIGHT_H_ */
