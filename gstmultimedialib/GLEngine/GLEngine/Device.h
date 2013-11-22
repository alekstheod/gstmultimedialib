#pragma once
#include <GL/gl.h>
#include <GL/glu.h>
#include <map>
#include <set>
#include <Utilities/Memory/SmartPtr/SharedPtr.h>
#include <Utilities/AutoLock/Mutex.h>
#include <GLEngine/GLException.h>

namespace gl {

class ICamera;
class IModel;
class ILight;
class Texture;

class Device {
public:
    struct RECT {
        int left;
        int top;
        int right;
        int bottom;
    };

public:
    static const GLuint CONST_INVALID_TEXTURE;

private:
    utils::Mutex m_lockObject;
    bool m_isOpenGLInitialized;
    bool m_windowWasResized;
    unsigned int m_windowWidth;
    unsigned int m_windowHeight;
    std::set<utils::SharedPtr<IModel> >m_glModels;
    utils::SharedPtr<ICamera> m_camera;
    std::set< utils::SharedPtr<ILight> > m_lights;
    std::map<GLuint, utils::SharedPtr<Texture> > m_textures;

public:
    Device(const Device::RECT&) throw (GLException);
    bool drawModels(void);
    bool setCamera(const utils::SharedPtr<ICamera>& camera);
    bool addGLModel(const utils::SharedPtr<IModel>& glModel);
    bool removeGLModel(const utils::SharedPtr<IModel>& glModel);
    bool setPerspective(unsigned int windowWidth, unsigned int windowHeight);
    bool removeLight(const utils::SharedPtr<ILight>& light);
    bool setLight(const utils::SharedPtr<ILight>& light);
    bool generateTexture(utils::SharedPtr<Texture>& newTexture);
    bool releaseTexture(const utils::SharedPtr<Texture>& texture);
    virtual ~Device(void) throw ();
};

}
