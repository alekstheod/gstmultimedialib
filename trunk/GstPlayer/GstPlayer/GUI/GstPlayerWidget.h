#ifndef GSTPLAYERWIDGET_H
#define GSTPLAYERWIDGET_H

#include <QtOpenGL/QGLWidget>
#include "ui_gstplayer.h"
#include <GLEngine/GLDevice.h>
#include <GstPlayer/VideoTrack.h>
#include <qtimer.h>

namespace gstplayer{

	class GstPlayerWidget : public QGLWidget
	{
		Q_OBJECT
		private:
			Ui::GstPlayerClass ui;
			utils::SmartPtr< gl::GLDevice > _glDevice;
			utils::SmartPtr< VideoTrack > _player;
			utils::SmartPtr<gl::IGLCamera> _camera;
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
