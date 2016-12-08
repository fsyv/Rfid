#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

namespace Ui {
class AdministratorMainwindow;
}

class AdministratorMainwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorMainwindow(QWidget *parent = 0);
    ~AdministratorMainwindow();

private slots:
    void on_Determine_clicked();

    void on_EmployeeInformation_activated(const QModelIndex &index);

    void on_Cancel_clicked();

private:
    Ui::AdministratorMainwindow *ui;

};

#endif // MAINWINDOW_H
