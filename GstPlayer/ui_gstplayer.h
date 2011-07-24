/********************************************************************************
** Form generated from reading UI file 'gstplayer.ui'
**
** Created: Sun Jul 24 15:57:13 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSTPLAYER_H
#define UI_GSTPLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GstPlayerClass
{
public:

    void setupUi(QWidget *GstPlayerClass)
    {
        if (GstPlayerClass->objectName().isEmpty())
            GstPlayerClass->setObjectName(QString::fromUtf8("GstPlayerClass"));
        GstPlayerClass->resize(400, 300);

        retranslateUi(GstPlayerClass);

        QMetaObject::connectSlotsByName(GstPlayerClass);
    } // setupUi

    void retranslateUi(QWidget *GstPlayerClass)
    {
        GstPlayerClass->setWindowTitle(QApplication::translate("GstPlayerClass", "GstPlayer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GstPlayerClass: public Ui_GstPlayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSTPLAYER_H
