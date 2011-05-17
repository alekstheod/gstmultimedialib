/*
 * IGLCamera.h
 *
 *  Created on: May 17, 2011
 *      Author: m1cRo
 */

#ifndef IGLCAMERA_H_
#define IGLCAMERA_H_
#include <GLEngine/GLVertex.h>

namespace gl {

	class IGLCamera {
		public:
			IGLCamera();
			virtual void setPosition(const GLVertex& position)=0;
			virtual void lookAt(const GLVertex& position)=0;
			virtual void applyCamera()=0;
			virtual ~IGLCamera();
	};

}

#endif /* IGLCAMERA_H_ */
