#include "rfidmainwindow.h"
#include "ui_rfidmainwindow.h"

RfidMainWindow::RfidMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RfidMainWindow)
{
    ui->setupUi(this);
}

RfidMainWindow::~RfidMainWindow()
{
    delete ui;
}
