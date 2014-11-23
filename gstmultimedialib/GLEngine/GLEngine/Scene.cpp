#include "Scene.h"
#include <GLEngine/Model/IModel.h>
#include <GLEngine/Camera/ICamera.h>
#include <GLEngine/Light/ILight.h>
#include <GLEngine/Model/Vertex.h>
#include <GLEngine/Model/Texture.h>
#include <Utilities/AutoLock/Mutex.h>
#include <algorithm>

using namespace std;
using namespace utils;

namespace std {
bool operator < (const std::reference_wrapper<gl::IModel> first, const gl::IModel& second) {
    return &first.get() < &second;
}

bool operator < (const gl::IModel& first, const std::reference_wrapper<gl::IModel> second) {
    return &first < &second.get();
}
}

namespace gl
{

Scene::Scene ( const Scene::RECT& windowRect ) throw ( GLException )
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

Scene::~Scene () throw ()
{
}

void Scene::drawImpl ()
{
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity();
    if ( m_camera != NULL ) {
        m_camera->applyCamera();
    }

    using namespace std::placeholders;
    std::for_each(m_glModels.begin(), m_glModels.end(), std::bind( &IModel::draw, _1 ));
    glFlush();
}

void Scene::addGLModel ( IModel& glModel )
{
    m_glModels.insert( std::upper_bound(m_glModels.begin(), m_glModels.end(), glModel ), glModel );
    m_glModels.push_back ( glModel );
}

bool Scene::removeGLModel ( IModel& glModel )
{
    bool result = false;
    auto i = std::lower_bound(m_glModels.begin(), m_glModels.end(), glModel);
    if ( i != m_glModels.end() ) {
        m_glModels.erase ( i );
        result = true;
    }

    return result;
}

void Scene::setPerspective ( unsigned int windowWidth,
                              unsigned int windowHeight )
{
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective ( 50.0, 1.0, 1.0, 10000.0 );
    glViewport ( 0, 0, windowWidth, windowHeight );
    glMatrixMode ( GL_MODELVIEW );
}

void Scene::setCamera ( const utils::SharedPtr<ICamera>& camera )
{
    m_camera = camera;
}

}

