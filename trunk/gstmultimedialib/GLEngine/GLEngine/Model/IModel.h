#pragma once
#include <string>
#include <GLEngine/Model/Vertex.h>

namespace gl {

class IModel {
private:
    /// @brief model draw method implementation.
    virtual bool drawImpl() = 0;

public:
    /// @brief will draw the model.
    /// @return true if succeed, false otherwise.
    bool draw(){
      return drawImpl();
    }
    
    virtual ~IModel() {}
};

}
