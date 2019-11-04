#include <QApplication>
#include <QGLFormat>

#if defined(QT_STATIC)
#include <QtPlugin>
#if defined(_WIN32)
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);
Q_IMPORT_PLUGIN(QWindowsVistaStylePlugin);
#endif
#endif

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGLFormat glf = QGLFormat::defaultFormat();
    glf.setSampleBuffers(true);
    glf.setSamples(4);
    QGLFormat::setDefaultFormat(glf);

    MainWindow w;
    w.show();
    
    return a.exec();
}
