#pragma once

namespace gl {
class Vertex {
public:
    const float x;
    const float y;
    const float z;

public:
    Vertex(float posX  = 0.f, float posY = 0.f, float posZ = 0.f);
    const Vertex& operator = (const Vertex& other )const;
    ~Vertex();
};
}

