/*
 * IGLCamera.h
 *
 *  Created on: May 17, 2011
 *      Author: m1cRo
 */

#ifndef IGLCAMERA_H_
#define IGLCAMERA_H_
#include <GLEngine/Model/Vertex.h>

namespace gl {

class ICamera {
public:
    ICamera();
    virtual void setPosition(const Vertex& position)=0;
    virtual void lookAt(const Vertex& position)=0;
    virtual void apply()=0;
    virtual ~ICamera();
};

}

#endif /* IGLCAMERA_H_ */
