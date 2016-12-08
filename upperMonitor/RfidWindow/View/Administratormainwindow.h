#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Determine_clicked();

    void on_EmployeeInformation_activated(const QModelIndex &index);

    void on_Cancel_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
