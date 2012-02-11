#ifndef GSTPLAYERWIDGET_H
#define GSTPLAYERWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <GLEngine/Device.h>
#include <GstPlayer/VideoTrack.h>
#include <qtimer.h>

namespace gstplayer {

class GstPlayerWidget: public QGLWidget {
private:
	utils::SmartPtr<gl::Device> _glDevice;
	utils::SmartPtr<VideoTrack> _track;
	utils::SmartPtr<gl::ICamera> _camera;
	utils::SmartPtr<gl::IModel> _menu;
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
