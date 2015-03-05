#ifndef LIGHTMODEL_H
#define LIGHTMODEL_H
#include <GLEngine/Model/Model.h>

namespace gl{
  
class WhiteLightModel : public Model
{
public:
  WhiteLightModel(){}
  ~WhiteLightModel(){}
  
private:
  void drawImpl();
};

}

#endif // LIGHTMODEL_H
