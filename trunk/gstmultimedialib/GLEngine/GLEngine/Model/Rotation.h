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
    float angle;
    float x;
    float y;
    float z;

    Rotation();
    Rotation ( float angle, float xAxis, float yAxis, float zAxis );
    virtual ~Rotation();
};

}


#endif /* ROTATION_H_ */
