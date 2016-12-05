#include "View/login.h"
#include <QApplication>
#include <qDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login w;
    w.show();

    return a.exec();
}
