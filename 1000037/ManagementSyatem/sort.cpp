#include "sort.h"
#include "ui_sort.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>    //sql语句
#include <QVariantList>
#include "database.h"
#include "enter.h"
Sort::Sort(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sort)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
    setFixedSize(383,277);                     // 禁止拖动窗口大小
    setWindowTitle("搜索");
}

Sort::~Sort()
{
    delete ui;
}

void Sort::on_pushButton_clicked()
{
    if(ui->lineEdit->text()!="")
    {

        QSqlQuery query;
        QString sql = QString("select * from ord where telephone=%1").arg(ui->lineEdit->text());
        query.exec(sql);
        while(query.next())
        {
            Order ord;
            //id,time,telephone,address,workname,work,retu,remark,receipt,admin
            ord.id = query.value("id").toInt();
            ord.time=query.value("time").toString();
            ord.telephone = query.value("telephone").toString();
            ord.address=query.value("address").toString();
            ord.workname = query.value("workname").toString();
            ord.work=query.value("work").toString();
            ord.retu = query.value("retu").toInt();
            ord.remark=query.value("remark").toString();
            ord.receipt=query.value("receipt").toString();
            ord.admin = query.value("admin").toInt();
            Enter *temp = new Enter;
            temp->outPut(ord);
            temp->show();

        }

    }




}
