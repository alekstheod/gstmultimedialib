#pragma once
#include <string>
#include <functional>
#include <GLEngine/Model/Vertex.h>

namespace gl {

class IModel {
private:
    /// @brief model draw method implementation.
    virtual void drawImpl() = 0;

public:
    /// @brief will draw the model.
    /// @return true if succeed, false otherwise.
    void draw(){
      drawImpl();
    }
    
    virtual ~IModel() {}
};

}
