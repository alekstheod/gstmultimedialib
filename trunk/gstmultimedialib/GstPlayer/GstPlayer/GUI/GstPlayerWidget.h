#ifndef GSTPLAYERWIDGET_H
#define GSTPLAYERWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <GLEngine/Scene.h>
#include <GstPlayer/VideoTrack.h>
#include <qtimer.h>
#include <memory>

namespace gstplayer {

class GstPlayerWidget: public QGLWidget {
private:
	std::unique_ptr<gl::Scene> m_glDevice;
	std::unique_ptr<VideoTrack> _track;
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
