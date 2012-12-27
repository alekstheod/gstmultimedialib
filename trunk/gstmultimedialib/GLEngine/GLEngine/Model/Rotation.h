/*
 * Rotation.h
 *
 *  Created on: May 24, 2011
 *      Author: m1cRo
 */

#ifndef ROTATION_H_
#define ROTATION_H_

namespace gl {

class Rotation {
public:
	float _angle;
	float x;
	float y;
	float z;

public:
	Rotation();
	Rotation(float angle, float xAxis, float yAxis, float zAxis);
	virtual ~Rotation();
};

}


#endif /* ROTATION_H_ */
