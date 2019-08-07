#ifndef LANDWIDGET_H
#define LANDWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>    //sql语句
#include <QVariantList>
namespace Ui {
class LandWidget;
}

class LandWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LandWidget(QWidget *parent = nullptr);
    ~LandWidget();
    void compare(QString userId,QString passWord);    //比较数据库里是否存在该用户以及用户名、密码、验证码是否正确
    int gro = 0;
    int idactive;
signals:
    void landSucceed(); //登陆成功信号
private slots:
    void on_LandButton_clicked();

public slots:
private:
    Ui::LandWidget *ui;


};

#endif // LANDWIDGET_H
