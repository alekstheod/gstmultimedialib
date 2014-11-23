#include "GstPlayerWidget.h"
#include <GLEngine/Camera/SimpleCamera.h>
#include <GstPlayer/GUI/Menu/MenuModel.h>

namespace gstplayer {

GstPlayerWidget::GstPlayerWidget(QWidget *parent) : QGLWidget(parent) {
    _timer.setInterval(20);
    connect(&_timer, SIGNAL( timeout() ), this, SLOT(updateScene()));
}

GstPlayerWidget::~GstPlayerWidget() {
}

void GstPlayerWidget::initializeGL() {
    QRect qRect = this->geometry();
    gl::Scene::RECT rect;
    rect.left = qRect.left();
    rect.right = qRect.right();
    rect.top = qRect.top();
    rect.bottom = qRect.bottom();
    m_glDevice.reset(new gl::Scene(rect));
    _camera = new gl::SimpleCamera;
    _camera->setPosition(gl::Vertex(0.0f, 0.0f, 2.3f));
    m_glDevice->setCamera(_camera);
    _menu = new MenuModel;
    //m_glDevice->addGLModel(_menu);
    _track.reset( new VideoTrack( "file:///run/media/alekstheod/D/Multimedia//test.avi", *m_glDevice) );
    _track->start(QThread::NormalPriority);
    _timer.start(20);
}

void GstPlayerWidget::resizeGL(int width, int height) {
    m_glDevice->setPerspective(width, height);
}

void GstPlayerWidget::paintGL() {
    m_glDevice->draw();
    this->update();
}

void GstPlayerWidget::updateScene() {
    paintGL();
}
}


