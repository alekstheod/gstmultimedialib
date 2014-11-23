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
class Scene : public IModel {
public:
    template<typename T>
    struct RECT {
        const T left;
        const T top;
        const T right;
        const T bottom;

        RECT(int l, int t, int r, int b) : left(l), top(t), right(r), bottom(b) {
            if ( left >= right ) {
                throw GLException ( "GLDevice::GLDevice - Wrong window rect" );
            }

            if ( top >= bottom ) {
                throw GLException ( "GLDevice::GLDevice - Wrong window rect" );
            }
        }
    };

private:
    bool m_isOpenGLInitialized;
    bool m_windowWasResized;
    unsigned int m_windowWidth;
    unsigned int m_windowHeight;
    std::vector< std::reference_wrapper<IModel> > m_glModels;
    ICamera& m_camera;

private:
    void drawImpl();

public:
    Scene(const Scene::RECT<int>&, ICamera& camera);
    void add(IModel& glModel);
    bool remove(IModel& glModel);
    void setPerspective(unsigned int windowWidth, unsigned int windowHeight);
    virtual ~Scene();
};

}
