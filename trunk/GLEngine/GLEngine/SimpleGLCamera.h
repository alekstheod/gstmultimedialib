/*
 * SimpleGLCamera.h
 *
 *  Created on: May 17, 2011
 *      Author: m1cRo
 */

#ifndef SIMPLEGLCAMERA_H_
#define SIMPLEGLCAMERA_H_

#include <GLEngine/IGLCamera.h>

namespace gl {

	class SimpleGLCamera: public gl::IGLCamera {
		public:
			static const GLVertex CONST_DEFAULT_CAMERA_POSITION;
			static const GLVertex CONST_DEFAULT_LOOKAT_POSITION;

		private:
			GLVertex _cameraPosition;
			GLVertex _lookAtPosition;

		public:
			SimpleGLCamera();
			void setPosition(const GLVertex& position);
			void lookAt(const GLVertex& position);
			void applyCamera();
			virtual ~SimpleGLCamera();
	};

}

#endif /* SIMPLEGLCAMERA_H_ */
