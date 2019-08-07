#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "landwidget.h"
#include "enter.h"
#include "browse.h"
#include "sort.h"
#include "database.h"
#include "admin.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_enterButton_clicked();

    void on_browseButton_clicked();

    void on_sortButton_clicked();

    void on_helpButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    LandWidget *land;
    Enter *enter;   //录入
    Browse *bro;    //浏览
    Sort *sort; //搜索
    DataBase datatabase;    //数据库
    int gro;    //权限
    int idactive;
    Admin *admin;
};

#endif // WIDGET_H
