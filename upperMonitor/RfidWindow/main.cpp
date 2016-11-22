#include "View/rfidmainwindow.h"
#include <QApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <qDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RfidMainWindow w;
    w.show();



    return a.exec();
}
