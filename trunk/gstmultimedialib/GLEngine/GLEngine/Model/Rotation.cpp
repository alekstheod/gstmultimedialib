/*
 * Rotation.cpp
 *
 *  Created on: May 24, 2011
 *      Author: m1cRo
 */

#include "Rotation.h"

namespace gl {

namespace wavefront {

Rotation::Rotation() {
	_angle = 0;
	_xAxis = 0;
	_yAxis = 0;
	_zAxis = 0;
}

Rotation::Rotation(float angle, float xAxis, float yAxis, float zAxis) {
	_angle = angle;
	_xAxis = xAxis;
	_yAxis = yAxis;
	_zAxis = zAxis;
}

Rotation::~Rotation() {
	// TODO Auto-generated destructor stub
}

float Rotation::getAngle() {
	return _angle;
}

float Rotation::getAxisX() {
	return _xAxis;
}

float Rotation::getAxisY() {
	return _yAxis;
}

float Rotation::getAxisZ() {
	return _zAxis;
}

}

}
