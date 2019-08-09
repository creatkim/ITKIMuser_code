#include "change.h"
#include "ui_change.h"
#include "enter.h"
#include "database.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>    //sql语句
Change::Change(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Change)
{
    ui->setupUi(this);
    this->id = id;
    QSqlQuery query;
    query.exec(QString("select * from ord where id = %1").arg(id));
    while(query.next()) //一行一行遍历
    {
        QString re;
        if(query.value("retu").toInt()==0)
        {
            re = "无";
        }
        else {
            re = "有";
        }
        ui->num->setText(QString("%1").arg(id));
        ui->time->setText(query.value("time").toString());
        ui->tele->setText(query.value("telephone").toString());
        ui->work->setText(query.value("work").toString());
        ui->address->setText(query.value("address").toString());
        ui->worker->setText(query.value("workname").toString());
        ui->retur->setText(re);
        ui->beizhu->setText(query.value("remark").toString());
         ui->shufei->setText(query.value("shufei").toString());
          ui->baojia->setText(query.value("baojia").toString());
//        QStandardItem *standItem1 = new QStandardItem(tr("%1").arg(temp->id));
//        QStandardItem *standItem2 = new QStandardItem(tr("%1").arg(query.value("time").toString()));
//        QStandardItem *standItem3 = new QStandardItem(tr("%1").arg(query.value("telephone").toString()));
//        QStandardItem *standItem4 = new QStandardItem(tr("%1").arg(query.value("work").toString()));
//        QStandardItem *standItem5 = new QStandardItem(tr("%1").arg(query.value("address").toString()));
//        QStandardItem *standItem6 = new QStandardItem(tr("%1").arg(query.value("workname").toString()));
//        QStandardItem *standItem7 = new QStandardItem(tr("%1").arg(re));
//        QStandardItem *standItem8 = new QStandardItem(tr("%1").arg(query.value("admin").toInt()));
//        QStandardItem *standItem9 = new QStandardItem(tr("%1").arg(query.value("remark").toString()));

    }

}

Change::~Change()
{
    delete ui;
}

void Change::on_pushButton_clicked()
{
    //点击修改
    int re;
    if(ui->retur->text()=="无")
    {
        re = 0;
    }
    else {
        re = 1;
    }
    QSqlQuery query;
//    QString sql = QString("insert into head(a,b,c,d,e,f,g,h,i) values('%1','%2','%3','%4','%5','%6','%7','%8','%9');")
//            .arg(ui->a->text()).arg(ui->b->text()).arg(ui->c->text())
//            .arg(ui->d->text()).arg(ui->e->text()).arg(ui->f->text())
//            .arg(ui->g->text()).arg(ui->h->text()).arg(ui->i->text());
    QString sql = QString("update ord set time= '%1',telephone= '%2',work= '%3',address= '%4',workname= '%5',retu= %6,remark= '%7',shufei=%8,baojia=%9 where id = %10")
            .arg(ui->time->text()).arg(ui->tele->text()).arg(ui->work->text())
                  .arg(ui->address->text()).arg(ui->worker->text()).arg(re)
                  .arg(ui->beizhu->text()).arg(ui->shufei->text()).arg(ui->baojia->text()).arg(id);
    qDebug()<<sql;
    if(query.exec(sql))
    {
        QMessageBox::warning(this,QStringLiteral("提示"),QStringLiteral("修改成功\n重新加载后显示"));
        this->close();
    }
    else{
        QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("修改失败，未知错误"));
    }

}
