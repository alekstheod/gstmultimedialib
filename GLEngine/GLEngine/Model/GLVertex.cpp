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

	float GLVertex::getPosX(void) const {
	    return _posX;
	}

	float GLVertex::getPosY(void) const {
	    return _posY;
	}

	float GLVertex::getPosZ(void) const {
	    return _posZ;
	}

	void GLVertex::setPosX(float posX) {
	    _posX = posX;
	}

	void GLVertex::setPosY(float posY) {
	    _posY = posY;
	}

	void GLVertex::setPosZ(float posZ) {
	    _posZ = posZ;
	}
}
