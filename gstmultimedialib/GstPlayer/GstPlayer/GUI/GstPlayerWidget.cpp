#include "GstPlayerWidget.h"
#include <GLEngine/Camera/SimpleCamera.h>
#include <GstPlayer/GUI/Menu/MenuModel.h>

namespace gstplayer {

GstPlayerWidget::GstPlayerWidget(QWidget *parent) : QGLWidget(parent) {
	_timer.setInterval(20);
	_timer.connect(&_timer, SIGNAL(timeout()), this, SLOT(updateScene()));
}

GstPlayerWidget::~GstPlayerWidget() {
}

void GstPlayerWidget::initializeGL() {
	QRect qRect = this->geometry();
	gl::Device::RECT rect;
	rect.left = qRect.left();
	rect.right = qRect.right();
	rect.top = qRect.top();
	rect.bottom = qRect.bottom();
	_glDevice = new gl::Device(rect);
	_camera = new gl::SimpleCamera;
	_camera->setPosition(gl::Vertex(0.0f, 0.0f, 2.3f));
	_glDevice->setCamera(_camera);
	_menu = new MenuModel;
	_glDevice->addGLModel(_menu);
	_track = new VideoTrack(
			"file:///home/alekstheod/Documents/test.avi",
			_glDevice);
	_track->start(QThread::NormalPriority);
	_timer.start(20);
}

void GstPlayerWidget::resizeGL(int width, int height) {
	_glDevice->setPerspective(width, height);
}

void GstPlayerWidget::paintGL() {
	_glDevice->drawModels();
	this->update();
}

void GstPlayerWidget::updateScene() {
	paintGL();
}
}

