#include "mainwindow.h"
#include <QApplication>

#include <Windows.h>
#include <cstdlib>

int main(int argc, char *argv[])
{
//    std::system("chcp 1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
