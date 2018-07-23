#include <QApplication>
#include "mainwindow.h"
#include<QWidget>
#include <QMainWindow>
#include <menuwindow.h>



int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    MenuWindow a;
    a.show();
    //MainWindow window;
    //window.show();
    return app.exec();
}
