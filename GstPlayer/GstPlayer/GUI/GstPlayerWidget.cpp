#include "GstPlayerWidget.h"
#include <GLEngine/Camera/SimpleGLCamera.h>
#include <GstPlayer/GUI/Menu/MenuGLModel.h>

namespace gstplayer{

	GstPlayerWidget::GstPlayerWidget(QWidget *parent) : QGLWidget(parent){
		ui.setupUi(this);
		_timer.setInterval(20);
		_timer.connect(&_timer, SIGNAL(timeout()), this, SLOT(updateScene()));
	}


	GstPlayerWidget::~GstPlayerWidget(){
	}


	void GstPlayerWidget::initializeGL(){
		QRect qRect=this->geometry();
		gl::GLDevice::RECT rect;
		rect.left=qRect.left();
		rect.right=qRect.right();
		rect.top=qRect.top();
		rect.bottom=qRect.bottom();
		_glDevice=new gl::GLDevice(rect);
		_camera=new gl::SimpleGLCamera;
		_camera->setPosition(gl::GLVertex(0.0f,0.0f,2.3f));
		_glDevice->setCamera(_camera);
		_menu=new MenuGLModel;
		_glDevice->addGLModel(_menu);
		_track=new VideoTrack("file:///home/alekstheod/Downloads/battle/test.avi",_glDevice);
		_track->start(QThread::NormalPriority);
		_timer.start(20);
	}


	void GstPlayerWidget::resizeGL(int width, int height){
		_glDevice->setPerspective(width, height);
	}


	void GstPlayerWidget::paintGL(){
		_glDevice->drawModels();
		this->update();
	}

	void GstPlayerWidget::updateScene(){
		paintGL();
	}
}

