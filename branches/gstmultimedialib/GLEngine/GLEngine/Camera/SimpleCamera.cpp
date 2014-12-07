/*
 * SimpleGLCamera.cpp
 *
 *  Created on: May 17, 2011
 *      Author: m1cRo
 */

#include "SimpleCamera.h"
#include <GL/glu.h>

namespace gl {

const Vertex SimpleCamera::CONST_DEFAULT_CAMERA_POSITION = Vertex(0.0f, 0.0f,
		5.41f);
const Vertex SimpleCamera::CONST_DEFAULT_LOOKAT_POSITION = Vertex(0.0f, 0.0f,
		0.0f);

SimpleCamera::SimpleCamera() :
		_cameraPosition(CONST_DEFAULT_CAMERA_POSITION), _lookAtPosition(
				CONST_DEFAULT_LOOKAT_POSITION) {
}

SimpleCamera::~SimpleCamera() {
}

void SimpleCamera::setPosition(const Vertex& position) {
	_cameraPosition = position;
}

void SimpleCamera::lookAt(const Vertex& position) {
	_lookAtPosition = position;
}

void SimpleCamera::applyCamera() {
	gluLookAt(_cameraPosition.x, _cameraPosition.y,
			_cameraPosition.z, _lookAtPosition.x,
			_lookAtPosition.y, _lookAtPosition.y, 0.0, 1.0,
			0.0);
}
}
