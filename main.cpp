// main.cpp — 程序入口
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("ElectricalPowerMonitor");
    app.setApplicationVersion("1.0");

    MainWindow w;
    w.show();

    return app.exec();
}
