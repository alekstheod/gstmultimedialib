#pragma once
#include <GL/gl.h>
#include <GL/glu.h>
#include <map>
#include <vector>
#include <set>
#include <Utilities/Memory/SmartPtr/SharedPtr.h>
#include <GLEngine/GLException.h>
#include <GLEngine/Model/IModel.h>

namespace gl {

class ICamera;
class ILight;
class Texture;

class Scene : public IModel {
public:
    struct RECT {
        int left;
        int top;
        int right;
        int bottom;
    };

private:
    bool m_isOpenGLInitialized;
    bool m_windowWasResized;
    unsigned int m_windowWidth;
    unsigned int m_windowHeight;
    std::vector< std::reference_wrapper<IModel> > m_glModels;
    std::vector< std::reference_wrapper<ILight> > m_lights;
    utils::SharedPtr<ICamera> m_camera;

private:
    void drawImpl();

public:
    Scene(const Scene::RECT&) throw (GLException);

    void setCamera(const utils::SharedPtr<ICamera>& camera);
    void addGLModel(IModel& glModel);
    bool removeGLModel(IModel& glModel);
    void setPerspective(unsigned int windowWidth, unsigned int windowHeight);
    virtual ~Scene() throw ();
};

}
