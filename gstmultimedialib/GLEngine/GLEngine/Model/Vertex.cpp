#include "Vertex.h"

namespace gl {
Vertex::Vertex(float posX, float posY, float posZ) :
		_posX(posX), _posY(posY), _posZ(posZ) {
}

Vertex::Vertex(void) {
	_posX = 0.0f;
	_posY = 0.0f;
	_posZ = 0.0f;
}

Vertex::~Vertex(void) {
}

float Vertex::getPosX(void) const {
	return _posX;
}

float Vertex::getPosY(void) const {
	return _posY;
}

float Vertex::getPosZ(void) const {
	return _posZ;
}

void Vertex::setPosX(float posX) {
	_posX = posX;
}

void Vertex::setPosY(float posY) {
	_posY = posY;
}

void Vertex::setPosZ(float posZ) {
	_posZ = posZ;
}
}
