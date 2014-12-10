#include "GstPlayerWidget.h"
#include <GLEngine/Camera/SimpleCamera.h>
#include <chrono>
#include <thread>
#include <boost/units/unit.hpp>
#include <GLEngine/Rect.h>


namespace gstplayer {

GstPlayerWidget::GstPlayerWidget(QWidget *parent) : QGLWidget(parent), 
						    m_assimp("/home/alekstheod/Downloads/assimp-3.1.1/test/models-nonbsd/3DS/mar_rifle.3ds") {
    m_timer.setInterval(20);
    connect(&m_timer, SIGNAL( timeout() ), this, SLOT(updateScene()));
}

GstPlayerWidget::~GstPlayerWidget() {
}

void GstPlayerWidget::initializeGL() {
    QRect qRect = this->geometry();
    gl::Rect<int> rect(qRect.left(), qRect.top(), qRect.right(), qRect.bottom());
    m_scene.reset(new gl::Scene(rect, m_camera));
    m_camera.setPosition(gl::Vertex(0.0f, 0.0f, 2.3f));
    m_track.reset( new VideoTrack( "file:///run/media/alekstheod/D/Multimedia//test.divx", *m_scene) );;
    m_assimp.move(gl::Vertex(0.f, 0.f, -95.f));
    m_scene->add(m_assimp);
    m_scene->add(m_light);
    m_track->start(QThread::NormalPriority);
    m_timer.start(20);
}

void GstPlayerWidget::resizeGL(int width, int height) {
    m_scene->setPerspective(width, height);
}

void GstPlayerWidget::paintGL() {
    m_scene->draw();
    m_assimp.rotate(gl::Rotation(3.f, 0.f, 2.f, 0.f));
    std::chrono::milliseconds dur( 20 );
    std::this_thread::sleep_for( dur );
    this->update();
}

void GstPlayerWidget::updateScene() {
    paintGL();
}
}


