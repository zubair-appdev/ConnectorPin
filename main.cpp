#include "mainwindow.h"
#include "defines.h"
#include <QApplication>

QList<int> pinArray;
QList<float> floatArray;
float angleOfRotation;
int totalPins;

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
