#include "Vertex.h"

namespace gl {
Vertex::Vertex(float posX, float posY, float posZ) :
		x(posX), y(posY), z(posZ) {
}

Vertex::Vertex(void) {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vertex::~Vertex(void) {
}

}
