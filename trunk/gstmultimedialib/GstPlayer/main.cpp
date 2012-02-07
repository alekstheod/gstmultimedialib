#include "GstPlayer/GUI/GstPlayerWidget.h"

#include <QtGui/QtGui>
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gstplayer::GstPlayerWidget w;
    w.show();
    int result = a.exec();
    return result;
}
