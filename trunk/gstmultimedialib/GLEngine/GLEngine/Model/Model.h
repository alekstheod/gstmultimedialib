#pragma once
#include <string>
#include <functional>
#include <GLEngine/Model/Vertex.h>
#include <GLEngine/Model/Rotation.h>
#include <GLEngine/Model/Vertex.h>

namespace gl {

class Model {
private:
   Rotation m_rotation;
   Vertex m_point;
  
private:
    /// @brief model draw method implementation.
    virtual void drawImpl() = 0;

public:
    /// @brief will draw the model.
    /// @return true if succeed, false otherwise.
    void draw();
    void move( const Vertex& offset );
    void rotate( const Rotation& rotation );
    virtual ~Model();
};

}
