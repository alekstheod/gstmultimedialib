#include "GstPlayer/GUI/GstPlayerWidget.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
	gst_init(&argc, &argv);
    QApplication a(argc, argv);
    gstplayer::GstPlayerWidget w;
    w.show();
    int result = a.exec();
    return result;
}
