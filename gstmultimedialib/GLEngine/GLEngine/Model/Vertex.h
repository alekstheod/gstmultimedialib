#pragma once

namespace gl {
class Vertex {
public:
	float x;
	float y;
	float z;

public:
	Vertex(void);
	Vertex(float posX, float posY, float posZ);
	~Vertex(void);
};
}

