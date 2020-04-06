#include "Database.h"
#include "mainwindow.h"
#include <QApplication>

Database myDB;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
