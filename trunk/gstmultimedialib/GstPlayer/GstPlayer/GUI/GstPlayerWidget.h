#ifndef GSTPLAYERWIDGET_H
#define GSTPLAYERWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <GLEngine/Device.h>
#include <GstPlayer/VideoTrack.h>
#include <qtimer.h>

namespace gstplayer {

class GstPlayerWidget: public QGLWidget {
private:
	utils::SharedPtr<gl::Device> _glDevice;
	utils::SharedPtr<VideoTrack> _track;
	utils::SharedPtr<gl::ICamera> _camera;
	utils::SharedPtr<gl::IModel> _menu;
	QTimer _timer;

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

private slots:
	void updateScene();

public:
	GstPlayerWidget(QWidget *parent = 0);
	~GstPlayerWidget();
};

}

#endif // GSTPLAYERWIDGET_H
