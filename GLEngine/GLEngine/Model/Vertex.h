#pragma once

namespace gl {
class Vertex {
public:
    float x;
    float y;
    float z;

public:
    Vertex(float posX  = 0.f, float posY = 0.f, float posZ = 0.f);
    ~Vertex();
};
}

