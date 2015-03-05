#include "Vertex.h"
#include <functional>

namespace gl {
Vertex::Vertex(float posX, float posY, float posZ) :
		x(posX), y(posY), z(posZ) {
}

Vertex::~Vertex(void) {
}

const Vertex& Vertex::operator = (const Vertex& other )const{
  const_cast<float&>( x ) = other.x;
  const_cast<float&>( y ) = other.y;
  const_cast<float&>( z ) = other.z;
  return *this;
}

}
