#include "Device.h"
#include <GLEngine/Model/IModel.h>
#include <GLEngine/Camera/ICamera.h>
#include <GLEngine/Light/ILight.h>
#include <GLEngine/Model/Vertex.h>
#include <GLEngine/Model/Texture.h>
#include <Utilities/AutoLock/Mutex.h>

using namespace std;
using namespace utils;

namespace gl
{

const GLuint Device::CONST_INVALID_TEXTURE = 0;

Device::Device ( const Device::RECT& windowRect ) throw ( GLException )
{
    if ( windowRect.left >= windowRect.right ) {
        throw GLException ( "GLDevice::GLDevice - Wrong window rect" );
    }

    if ( windowRect.top >= windowRect.bottom ) {
        throw GLException ( "GLDevice::GLDevice - Wrong window rect" );
    }

    glEnable ( GL_DEPTH_TEST );
    glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
    glMatrixMode ( GL_PROJECTION );
    glViewport ( 0, 0, windowRect.right - windowRect.left,
                 windowRect.bottom - windowRect.top );
    glMatrixMode ( GL_MODELVIEW );
}

Device::~Device ( void ) throw ()
{
}

bool Device::drawModels ( void )
{
    try {
        AutoLock<Mutex> lock ( m_lockObject );
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glMatrixMode ( GL_MODELVIEW );
        glLoadIdentity();
        ICamera* null = NULL;
        if ( m_camera != NULL ) {
            m_camera->applyCamera();
        }

        std::set< utils::SharedPtr<ILight> >::iterator curLight;
        for ( curLight = m_lights.begin(); curLight != m_lights.end();
                curLight++ ) {
            ( *curLight )->applyLight();
        }

        std::set< utils::SharedPtr<IModel> >::iterator glModel;
        for ( glModel = m_glModels.begin(); glModel != m_glModels.end();
                glModel++ ) {
            if ( ( *glModel )->draw() == false ) {
                return false;
            }
        }

        glFlush();
    } catch ( const LockException& ) {
        return false;
    }

    return true;
}

bool Device::addGLModel ( const SharedPtr<IModel>& glModel )
{
    try {
        AutoLock<Mutex> lock ( m_lockObject );
        if ( m_glModels.insert ( glModel ).second == false ) {
            return false;
        }
    } catch ( const LockException& ) {
        return false;
    }

    return true;
}

bool Device::removeGLModel ( const utils::SharedPtr<IModel>& glModel )
{
    try {
        utils::AutoLock<Mutex> lock ( m_lockObject );
        if ( m_glModels.find ( glModel ) == m_glModels.end() ) {
            return false;
        }

        m_glModels.erase ( glModel );
    } catch ( const utils::LockException& ) {
        return false;
    }

    return true;
}

bool Device::setPerspective ( unsigned int windowWidth,
                              unsigned int windowHeight )
{
    try {
        AutoLock<Mutex> lock ( m_lockObject );
        glMatrixMode ( GL_PROJECTION );
        glLoadIdentity();
        gluPerspective ( 50.0, 1.0, 1.0, 10000.0 );
        glViewport ( 0, 0, windowWidth, windowHeight );
        glMatrixMode ( GL_MODELVIEW );
    } catch ( const LockException& ) {
        return false;
    }

    return true;
}

bool Device::setCamera ( const utils::SharedPtr<ICamera>& camera )
{
    try {
        AutoLock<Mutex> lock ( m_lockObject );
        m_camera = camera;
    } catch ( const utils::LockException& ) {
        return false;
    }

    return true;
}

bool Device::removeLight ( const utils::SharedPtr<ILight>& light )
{
    try {
        utils::AutoLock<Mutex> lock ( m_lockObject );
        if ( m_lights.find ( light ) == m_lights.end() ) {
            return false;
        }

        m_lights.erase ( light );
    } catch ( const utils::LockException& ) {
        return false;
    }

    return true;
}

bool Device::setLight ( const utils::SharedPtr<ILight>& light )
{
    bool result = false;

    try {
        utils::AutoLock<Mutex> lock ( m_lockObject );
        result = m_lights.insert ( light ).second;
    } catch ( utils::LockException& ) {
        return result;
    }

    return result;
}

bool Device::generateTexture ( utils::SharedPtr<Texture>& newTexture )
{
    bool result = false;
    GLuint texture = CONST_INVALID_TEXTURE;
    if ( m_textures.empty() ) {
        texture = 1;
        newTexture.Attach ( new Texture ( texture ) );
        m_textures.insert ( std::make_pair(texture, newTexture) );
    } else {
        std::map<GLuint, utils::SharedPtr<Texture> >::iterator prevTexture;
        for ( auto curTexture = m_textures.begin();
                curTexture != m_textures.end()
                && texture == CONST_INVALID_TEXTURE; curTexture++ ) {
            if ( curTexture != m_textures.begin() ) {
                GLuint lastTexture = prevTexture->first;
                GLuint currentTexture = curTexture->first - 1;
                if ( lastTexture < currentTexture ) {
                    texture = lastTexture + 1;
                }
            }

            prevTexture = curTexture;
        }

        if ( texture != CONST_INVALID_TEXTURE ) {
            newTexture.Attach ( new Texture ( texture ) );
            result = m_textures.insert ( std::make_pair(texture, newTexture) ).second;
        } else {
            auto curTexture = ( --m_textures.end() );
            texture = curTexture->first + 1;
            newTexture = new Texture ( texture );
            result = m_textures.insert ( std::make_pair(texture, newTexture) ).second;
        }
    }

    return result;
}

bool Device::releaseTexture ( const utils::SharedPtr<Texture>& texture )
{
    bool result = false;
    if ( m_textures.find ( texture->m_texture ) != m_textures.end() ) {
        m_textures.erase ( texture->m_texture );
        result = true;
    }

    return result;
}
}

