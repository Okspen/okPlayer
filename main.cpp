#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	a.instance()->setApplicationName("okPlayer");
	a.instance()->setApplicationVersion("0.285");

	MainWindow w;
    w.show();
    return a.exec();
}
