#ifndef CHANGE_H
#define CHANGE_H

#include <QWidget>
#include "enter.h"
namespace Ui {
class Change;
}

class Change : public QWidget
{
    Q_OBJECT

public:
    explicit Change(int id, QWidget *parent = nullptr);
    ~Change();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Change *ui;
    int id;
};

#endif // CHANGE_H
