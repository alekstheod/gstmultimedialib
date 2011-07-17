/****************************************************************************
** Meta object code from reading C++ file 'GstPlayerWidget.h'
**
** Created: Sat Jul 16 17:18:54 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GstPlayer/GUI/GstPlayerWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GstPlayerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gstplayer__GstPlayerWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_gstplayer__GstPlayerWidget[] = {
    "gstplayer::GstPlayerWidget\0\0updateScene()\0"
};

const QMetaObject gstplayer::GstPlayerWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_gstplayer__GstPlayerWidget,
      qt_meta_data_gstplayer__GstPlayerWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gstplayer::GstPlayerWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gstplayer::GstPlayerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gstplayer::GstPlayerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gstplayer__GstPlayerWidget))
        return static_cast<void*>(const_cast< GstPlayerWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int gstplayer::GstPlayerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateScene(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
