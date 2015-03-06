#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.instance()->setOrganizationName("Okspen");
    a.instance()->setApplicationName("okPlayer");
    a.instance()->setApplicationVersion("0.3.2.0");

    MainWindow w;
    w.show();
    return a.exec();
}
