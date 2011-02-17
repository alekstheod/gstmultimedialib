#include "GLVertex.h"

namespace gl{
	GLVertex::GLVertex(float posX, float posY, float posZ) : _posX(posX), _posY(posY), _posZ(posZ) {
	}

	GLVertex::GLVertex(void) {
	    _posX = 0.0f;
	    _posY = 0.0f;
	    _posZ = 0.0f;
	}

	GLVertex::~GLVertex(void) {
	}

	float GLVertex::GetPosX(void) const {
	    return _posX;
	}

	float GLVertex::GetPosY(void) const {
	    return _posY;
	}

	float GLVertex::GetPosZ(void) const {
	    return _posZ;
	}

	void GLVertex::SetPosX(float posX) {
	    _posX = posX;
	}

	void GLVertex::SetPosY(float posY) {
	    _posY = posY;
	}

	void GLVertex::SetPosZ(float posZ) {
	    _posZ = posZ;
	}
}
