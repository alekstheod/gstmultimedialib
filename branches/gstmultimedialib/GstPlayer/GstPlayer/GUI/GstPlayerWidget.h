#ifndef GSTPLAYERWIDGET_H
#define GSTPLAYERWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <GLEngine/Scene.h>
#include <GLEngine/Camera/SimpleCamera.h>
#include <GstPlayer/VideoTrack.h>
#include <GstPlayer/GUI/Menu/MenuModel.h>
#include <qtimer.h>
#include <memory>

namespace gstplayer {

class GstPlayerWidget: public QGLWidget {
private:
    std::unique_ptr<gl::Scene> m_scene;
    std::unique_ptr<VideoTrack> m_track;
    gl::SimpleCamera m_camera;
    MenuModel m_menu;
    QTimer m_timer;

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
