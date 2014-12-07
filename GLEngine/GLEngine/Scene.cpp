#include "Scene.h"
#include <GLEngine/Model/Model.h>
#include <GLEngine/Camera/ICamera.h>
#include <GLEngine/Model/Vertex.h>
#include <GLEngine/Model/Texture.h>
#include <Utilities/AutoLock/Mutex.h>
#include <algorithm>

using namespace std;
using namespace utils;

namespace std {
bool operator < (const std::reference_wrapper<gl::Model> first, const gl::Model& second) {
    return &first.get() < &second;
}

bool operator < (const gl::Model& first, const std::reference_wrapper<gl::Model> second) {
    return &first < &second.get();
}
}

namespace gl
{

Scene::Scene ( const Scene::RECT<int>& windowRect, ICamera& camera ) : m_camera(camera)
{
    glEnable ( GL_DEPTH_TEST );
    glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
    glMatrixMode ( GL_PROJECTION );
    glViewport ( 0, 0, windowRect.right - windowRect.left,
                 windowRect.bottom - windowRect.top );
    glMatrixMode ( GL_MODELVIEW );
}

Scene::~Scene ()
{
}

void Scene::drawImpl ()
{
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity();
    m_camera.apply();
    using namespace std::placeholders;
    std::for_each(m_glModels.begin(), m_glModels.end(), std::bind( &Model::draw, _1 ));
    glFlush();
}

void Scene::add( Model& glModel )
{
    m_glModels.insert( std::upper_bound(m_glModels.begin(), m_glModels.end(), glModel ), glModel );
}

bool Scene::remove( Model& glModel )
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

}

