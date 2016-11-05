#ifndef RFIDMAINWINDOW_H
#define RFIDMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class RfidMainWindow;
}

class RfidMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RfidMainWindow(QWidget *parent = 0);
    ~RfidMainWindow();

private:
    Ui::RfidMainWindow *ui;
};

#endif // RFIDMAINWINDOW_H
