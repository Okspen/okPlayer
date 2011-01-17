#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    a.instance()->setApplicationName("okPlayer");
    a.instance()->setApplicationVersion("0.2861");

    MainWindow w;
    w.show();
    return a.exec();
}
