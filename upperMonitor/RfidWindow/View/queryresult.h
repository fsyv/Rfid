#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <QDialog>
#include <QByteArray>

namespace Ui {
class QueryResult;
}

class QueryResult : public QDialog
{
    Q_OBJECT

public:
    explicit QueryResult(QWidget *parent = 0);
    explicit QueryResult(QByteArray byteArray, QWidget *parent = 0);
    ~QueryResult();

private:
    Ui::QueryResult *ui;
};

#endif // QUERYRESULT_H
