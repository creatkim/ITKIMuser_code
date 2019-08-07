#ifndef SORT_H
#define SORT_H

#include <QWidget>
#include "enter.h"
namespace Ui {
class Sort;
}

class Sort : public QWidget
{
    Q_OBJECT

public:
    explicit Sort(QWidget *parent = nullptr);
    ~Sort();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Sort *ui;
};

#endif // SORT_H
