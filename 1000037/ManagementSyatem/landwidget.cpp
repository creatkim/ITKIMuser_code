#include "landwidget.h"
#include "ui_landwidget.h"
//#include "register.h"
#include <QMessageBox>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include "database.h"

LandWidget::LandWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LandWidget)
{
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
    setFixedSize(366,285);                     // 禁止拖动窗口大小

    ui->setupUi(this);
    setWindowTitle("登陆");


    ui->Password->setEchoMode(QLineEdit::Password); //设置密码编辑框为隐藏模式
  //  ui->UserName->setEchoMode(QLineEdit::Normal);

}

LandWidget::~LandWidget()
{
    delete ui;
}


void LandWidget::compare(QString userId, QString passWord)
{
/*    DataBase data;

    gro =data.dealLand(userId,passWord);
    if(0==gro)
    {
        emit landSucceed();
    }
    else if(gro == 1){
        emit landSucceed();
    }else {
        //密码错误
        QMessageBox::warning(this,QStringLiteral("密码错误"),QString("账号或密码错误"));
    }
*/
    QSqlQuery query;
    QString sql = QString("select password,gro from user where id = %1").arg(userId);
    query.exec(sql);
    while(query.next())
    {
        if(passWord == query.value("password").toString())
        {
            //密码正确
            gro=query.value("gro").toInt();
            idactive = userId.toInt();
            emit landSucceed();
        }else {
           QMessageBox::warning(this,QStringLiteral("密码错误"),QString("账号或密码错误"));
        }
    }
}

void LandWidget::on_LandButton_clicked()
{
    compare(ui->UserId->text(),ui->Password->text());
}
