/*
 * SimpleGLCamera.h
 *
 *  Created on: May 17, 2011
 *      Author: m1cRo
 */

#ifndef SIMPLEGLCAMERA_H_
#define SIMPLEGLCAMERA_H_

#include <GLEngine/Camera/ICamera.h>

namespace gl {

class SimpleCamera: public gl::ICamera {
public:
	static const Vertex CONST_DEFAULT_CAMERA_POSITION;
	static const Vertex CONST_DEFAULT_LOOKAT_POSITION;

private:
	Vertex _cameraPosition;
	Vertex _lookAtPosition;

public:
	SimpleCamera();
	void setPosition(const Vertex& position);
	void lookAt(const Vertex& position);
	void apply();
	virtual ~SimpleCamera();
};

}

#endif /* SIMPLEGLCAMERA_H_ */
