#pragma once
#include <GL/gl.h>
#include <GL/glu.h>
#include <map>
#include <vector>
#include <set>
#include <GLEngine/GLException.h>
#include <GLEngine/Model/Model.h>

namespace gl {

template<typename T>
struct Rect;
  
class ICamera;
class Scene : public Model {
private:
    std::vector< std::reference_wrapper<Model> > m_glModels;
    ICamera& m_camera;

private:
    void drawImpl();
    void drawModel( Model& model);

public:
    Scene(const Rect<int>&, ICamera& camera);
    void add(Model& glModel);
    bool remove(Model& glModel);
    void setPerspective(unsigned int width, unsigned int height);
    virtual ~Scene();
};

}
