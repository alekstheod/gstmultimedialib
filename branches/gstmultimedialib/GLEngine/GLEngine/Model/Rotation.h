/*
 * Rotation.h
 *
 *  Created on: May 24, 2011
 *      Author: m1cRo
 */

#ifndef ROTATION_H_
#define ROTATION_H_

namespace gl
{

struct Rotation {
    const float angle;
    const float x;
    const float y;
    const float z;
    Rotation ( float angle = 0.f, float xAxis = 0.f, float yAxis = 0.f, float zAxis = 0.f );
    ~Rotation();
};

}


#endif /* ROTATION_H_ */
