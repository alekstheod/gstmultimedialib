/*
 * Rotation.cpp
 *
 *  Created on: May 24, 2011
 *      Author: m1cRo
 */

#include "Rotation.h"

namespace gl
{

Rotation::Rotation()
{
    angle = 0;
    x = 0;
    y = 0;
    z = 0;
}

Rotation::Rotation ( float angle, float xAxis, float yAxis, float zAxis )
{
    angle = angle;
    x = xAxis;
    y = yAxis;
    z = zAxis;
}

Rotation::~Rotation()
{
}

}

