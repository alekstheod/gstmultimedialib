/*
 * SimpleGLCamera.cpp
 *
 *  Created on: May 17, 2011
 *      Author: m1cRo
 */

#include "SimpleGLCamera.h"
#include <GL/glu.h>

namespace gl {

	const GLVertex SimpleGLCamera::CONST_DEFAULT_CAMERA_POSITION=GLVertex(0.0f, 0.0f, 1.41f);
	const GLVertex SimpleGLCamera::CONST_DEFAULT_LOOKAT_POSITION=GLVertex(0.0f, 0.0f, 0.0f);

	SimpleGLCamera::SimpleGLCamera():_cameraPosition(CONST_DEFAULT_CAMERA_POSITION), _lookAtPosition(CONST_DEFAULT_LOOKAT_POSITION) {
	}

	SimpleGLCamera::~SimpleGLCamera() {
	}

	void SimpleGLCamera::setPosition(const GLVertex& position){
		_cameraPosition=position;
	}

	void SimpleGLCamera::lookAt(const GLVertex& position){
		_lookAtPosition=position;
	}

	void SimpleGLCamera::applyCamera(){
		gluLookAt(_cameraPosition.getPosX(), _cameraPosition.getPosY(), _cameraPosition.getPosZ(),
				_lookAtPosition.getPosX(), _lookAtPosition.getPosY(), _lookAtPosition.getPosZ(),
				0.0f, 1.0f, 0.0f);
	}
}
