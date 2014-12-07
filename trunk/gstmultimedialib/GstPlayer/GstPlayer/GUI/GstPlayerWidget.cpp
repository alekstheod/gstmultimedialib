#include "GstPlayerWidget.h"
#include <GLEngine/Camera/SimpleCamera.h>
#include <chrono>
#include <thread>

namespace gstplayer {

GstPlayerWidget::GstPlayerWidget(QWidget *parent) : QGLWidget(parent) {
    m_timer.setInterval(20);
    connect(&m_timer, SIGNAL( timeout() ), this, SLOT(updateScene()));
}

GstPlayerWidget::~GstPlayerWidget() {
}

void GstPlayerWidget::initializeGL() {
    QRect qRect = this->geometry();
    gl::Scene::RECT<int> rect(qRect.left(), qRect.top(), qRect.right(), qRect.bottom());
    m_scene.reset(new gl::Scene(rect, m_camera));
    m_camera.setPosition(gl::Vertex(0.0f, 0.0f, 2.3f));
    m_scene->add(m_menu);
    m_track.reset( new VideoTrack( "file:///run/media/alekstheod/D/Multimedia//test.avi", *m_scene) );
    m_track->start(QThread::NormalPriority);
    m_timer.start(20);
}

void GstPlayerWidget::resizeGL(int width, int height) {
    m_scene->setPerspective(width, height);
}

void GstPlayerWidget::paintGL() {
    m_scene->draw();
    std::chrono::milliseconds dura( 20 );
    std::this_thread::sleep_for( dura );
    this->update();
}

void GstPlayerWidget::updateScene() {
    paintGL();
}
}


