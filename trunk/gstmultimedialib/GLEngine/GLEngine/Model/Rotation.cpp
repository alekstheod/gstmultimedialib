/*
 * Rotation.cpp
 *
 *  Created on: May 24, 2011
 *      Author: m1cRo
 */

#include "Rotation.h"

namespace gl
{

Rotation::Rotation ( float angle, float xAxis, float yAxis, float zAxis ):angle(angle),
    x(xAxis),
    y(yAxis),
    z(zAxis) {}

Rotation& Rotation::operator = ( const Rotation& other ){
  const_cast<float&>(x) = other.x;
  const_cast<float&>(y)= other.y;
  const_cast<float&>(z)=other.z;
  const_cast<float&>(angle) = other.angle;
  return *this;
}    
    
Rotation::~Rotation()
{
}

}

