#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    setvbuf(stdout, (char * )NULL, _IONBF, 0);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
