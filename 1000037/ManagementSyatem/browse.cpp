﻿#include "browse.h"
#include "ui_browse.h"
#include "database.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>    //sql语句
#include <QVariantList>
#include <QPushButton>

Browse::Browse(int gro,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Browse)
{
    quanx =gro;
    ui->setupUi(this);
    if(quanx==0)
    {
        qDebug()<<"管理员"<<quanx;
        setFixedSize(1311,701);                     // 701禁止拖动窗口大小
    }else {
        qDebug()<<"普通用户"<<quanx;
            setFixedSize(1311,637);                     // 701禁止拖动窗口大小
    }
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮

    setWindowTitle("浏览");
    QSqlQuery query;
    QString sql = "create table head(id int primary key, a varchar(45),b varchar(45),c varchar(45),d varchar(45),e varchar(45),f varchar(45),g varchar(45),h varchar(45),i varchar(45));";

    if(query.exec(sql))
    {
        qDebug()<<"创建成功";
    }
    sql = "insert into head(id,a, b, c,d,e,f,g,h,i) values(1,'单号','时间','电话','项目','地址','维修工','电话回访','录入员','备注');";
    if(query.exec(sql))
    {
         qDebug()<<"插入成功";
    }

    sql = "select * from head";
    if(query.exec(sql))
    {
         qDebug()<<"查询成功";
    }

    standItemModel = new QStandardItemModel();
    standItemModel->setColumnCount(10);
    while(query.next())
    {
        standItemModel->setHeaderData(0,Qt::Horizontal,query.value("a").toString());   //设置表头内容
        ui->a->setText(query.value("a").toString());
        standItemModel->setHeaderData(1,Qt::Horizontal,query.value("b").toString());
        ui->b->setText(query.value("b").toString());
        standItemModel->setHeaderData(2,Qt::Horizontal,query.value("c").toString());
        ui->c->setText(query.value("c").toString());
        standItemModel->setHeaderData(3,Qt::Horizontal,query.value("d").toString());
        ui->d->setText(query.value("d").toString());
        standItemModel->setHeaderData(4,Qt::Horizontal,query.value("e").toString());
        ui->e->setText(query.value("e").toString());
        standItemModel->setHeaderData(5,Qt::Horizontal,query.value("f").toString());
        ui->f->setText(query.value("f").toString());
        standItemModel->setHeaderData(6,Qt::Horizontal,query.value("g").toString());
        ui->g->setText(query.value("g").toString());
        standItemModel->setHeaderData(7,Qt::Horizontal,query.value("h").toString());
        ui->h->setText(query.value("h").toString());
        standItemModel->setHeaderData(8,Qt::Horizontal,query.value("i").toString());
        ui->i->setText(query.value("i").toString());
    }

    /*
    standItemModel->setHeaderData(0,Qt::Horizontal,QStringLiteral("单号"));   //设置表头内容
    standItemModel->setHeaderData(1,Qt::Horizontal,QStringLiteral("时间"));
    standItemModel->setHeaderData(2,Qt::Horizontal,QStringLiteral("电话"));
    standItemModel->setHeaderData(3,Qt::Horizontal,QStringLiteral("项目"));
    standItemModel->setHeaderData(4,Qt::Horizontal,QStringLiteral("地址"));
    standItemModel->setHeaderData(5,Qt::Horizontal,QStringLiteral("维修工"));
    standItemModel->setHeaderData(6,Qt::Horizontal,QStringLiteral("电话回访"));
    standItemModel->setHeaderData(7,Qt::Horizontal,QStringLiteral("录入员"));
    standItemModel->setHeaderData(8,Qt::Horizontal,QStringLiteral("备注"));
    */
    standItemModel->setHeaderData(9,Qt::Horizontal,QStringLiteral("操作"));
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑
    int count = landInfo();
    ui->tableView->setModel(standItemModel);    //挂载表格模型

    for(int i=0;i<count;i++)
    {
        QPushButton *m_PushButton=new QPushButton;
        connect(m_PushButton,&QPushButton::clicked,
                [=]()
                {
                    qDebug()<<i;

                    QSqlQuery query;
                    QString sql = QString("delete from ord where id = %1;").arg(numToId(i));
                    if(query.exec(sql))
                    {
                        //从数据库中删除成功
                        qDebug()<<"删除 "<<sql;
                        QMessageBox::warning(this,QStringLiteral("提示"),QStringLiteral("删除成功"));
                        standItemModel->removeRow(i);                               //删除从第0行开始的连续10行

                    }else {
                        //删除失败
                        QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("删除失败"));
                    }


                }

                );
        m_PushButton->setText(QStringLiteral("删除"));
        ui->tableView->setIndexWidget(standItemModel->index(i,9),m_PushButton);    //向表格单元添加一个控件
    }
}
int Browse::numToId(int num)
{
    for(int i=0;i<idList.size();i++)
    {
        qDebug()<<idList.at(i)->num<<"id:"<<idList.at(i)->id;
    }
    int id = -1;
    for(int i=0;i<idList.size();i++)
    {
        if(idList.at(i)->num == num)
        {
            id = idList.at(i)->id;
        }
    }
    return id;
}
int Browse::landInfo()
{
    //从数据库中加载订单
    QSqlQuery query;
    query.exec("select * from ord");

    int i=0;
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
        ID *temp = new ID;
        temp->num = i;
        temp->id=query.value("id").toInt();
        idList.append(temp);
        QStandardItem *standItem1 = new QStandardItem(tr("%1").arg(temp->id));
        QStandardItem *standItem2 = new QStandardItem(tr("%1").arg(query.value("time").toString()));
        QStandardItem *standItem3 = new QStandardItem(tr("%1").arg(query.value("telephone").toString()));
        QStandardItem *standItem4 = new QStandardItem(tr("%1").arg(query.value("work").toString()));
        QStandardItem *standItem5 = new QStandardItem(tr("%1").arg(query.value("address").toString()));
        QStandardItem *standItem6 = new QStandardItem(tr("%1").arg(query.value("workname").toString()));
        QStandardItem *standItem7 = new QStandardItem(tr("%1").arg(re));
        QStandardItem *standItem8 = new QStandardItem(tr("%1").arg(query.value("admin").toInt()));
        QStandardItem *standItem9 = new QStandardItem(tr("%1").arg(query.value("remark").toString()));
        standItemModel->setItem(i,0,standItem1);                                //表格第i行，第0列添加一项内容
        //standItemModel->item(i,0)->setForeground(QBrush(QColor(255,0,0)));      //设置字符颜色
        standItemModel->item(i,0)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
        standItemModel->setItem(i,1,standItem2);                                //表格第i行，第1列添加一项内容
        standItemModel->setItem(i,2,standItem3);
        standItemModel->setItem(i,3,standItem4);
        standItemModel->setItem(i,4,standItem5);
        standItemModel->setItem(i,5,standItem6);
        standItemModel->setItem(i,6,standItem7);
        standItemModel->setItem(i,7,standItem8);
        standItemModel->setItem(i,8,standItem9);
        //QPushButton *m_PushButton=new QPushButton;
       // m_PushButton->setText(QStringLiteral("删除"));
       // ui->tableView->setIndexWidget(standItemModel->index(i,9),m_PushButton);    //向表格单元添加一个控件
        i++;
    }
    return i;
}
Browse::~Browse()
{
    delete ui;
}

void Browse::on_pushButton_clicked()
{
    //修改表头
    QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("确认修改？"));
    QSqlQuery query;
//    QString sql = QString("insert into head(a,b,c,d,e,f,g,h,i) values('%1','%2','%3','%4','%5','%6','%7','%8','%9');")
//            .arg(ui->a->text()).arg(ui->b->text()).arg(ui->c->text())
//            .arg(ui->d->text()).arg(ui->e->text()).arg(ui->f->text())
//            .arg(ui->g->text()).arg(ui->h->text()).arg(ui->i->text());
    QString sql = QString("update head set a = '%1',b= '%2',c= '%3',d= '%4',e= '%5',f= '%6',g= '%7',h= '%8',i= '%9' where id = 1")
            .arg(ui->a->text()).arg(ui->b->text()).arg(ui->c->text())
                  .arg(ui->d->text()).arg(ui->e->text()).arg(ui->f->text())
                  .arg(ui->g->text()).arg(ui->h->text()).arg(ui->i->text());
    if(query.exec(sql))
    {
        QMessageBox::warning(this,QStringLiteral("提示"),QStringLiteral("修改成功\n重新打开此界面后显示"));
    }
    else{
        QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("修改失败，未知错误"));
    }
}