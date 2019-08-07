#include "admin.h"
#include "ui_admin.h"
#include "database.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>    //sql语句
#include <QVariantList>
#include <QPushButton>
Admin::Admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
    setFixedSize(754,458);                     // 禁止拖动窗口大小
    setWindowTitle("系统管理");
    standItemModel = new QStandardItemModel();
    standItemModel->setColumnCount(5);
    standItemModel->setHeaderData(0,Qt::Horizontal,QStringLiteral("账号"));   //设置表头内容
    standItemModel->setHeaderData(1,Qt::Horizontal,QStringLiteral("姓名"));
    standItemModel->setHeaderData(2,Qt::Horizontal,QStringLiteral("密码"));
    standItemModel->setHeaderData(3,Qt::Horizontal,QStringLiteral("权限"));
    standItemModel->setHeaderData(4,Qt::Horizontal,QStringLiteral("管理"));
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑
    ui->tableView->setModel(standItemModel);    //挂载表格模型
    loadInfo();

}
int Admin::loadInfo()
{
    //从数据库中加载订单
    QSqlQuery query;
    query.exec("select * from user");

    int i=0;
    while(query.next()) //一行一行遍历
    {
        QString re;
        if(query.value("gro").toInt()==0)
        {
            re = "管理员";
        }
        else {
            re = "普通用户";
        }
        ID_ *temp = new ID_;
        temp->num = i;
        temp->id=query.value("id").toString();
        idList.append(temp);
        QStandardItem *standItem1 = new QStandardItem(tr("%1").arg(query.value("id").toString()));
        QStandardItem *standItem2 = new QStandardItem(tr("%1").arg(query.value("name").toString()));
        QStandardItem *standItem3 = new QStandardItem(tr("%1").arg(query.value("password").toString()));
        QStandardItem *standItem4 = new QStandardItem(tr("%1").arg(re));

        standItemModel->setItem(i,0,standItem1);                                //表格第i行，第0列添加一项内容
        //standItemModel->item(i,0)->setForeground(QBrush(QColor(255,0,0)));      //设置字符颜色
        standItemModel->item(i,0)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
        standItemModel->setItem(i,1,standItem2);                                //表格第i行，第1列添加一项内容
        standItemModel->setItem(i,2,standItem3);
        standItemModel->setItem(i,3,standItem4);

        QPushButton *m_PushButton=new QPushButton;
        m_PushButton->setText(QStringLiteral("删除"));
        ui->tableView->setIndexWidget(standItemModel->index(i,4),m_PushButton);    //向表格单元添加一个控件
        connect(m_PushButton,&QPushButton::clicked,
                [=]()
                {
                    qDebug()<<i;

                    QSqlQuery query;
                    QString sql = QString("delete from user where id = %1;").arg(numToId(i));
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
        i++;
    }
    return i;
}
QString Admin::numToId(int num)
{
    for(int i=0;i<idList.size();i++)
    {
        qDebug()<<idList.at(i)->num<<"id:"<<idList.at(i)->id;
    }
    QString id = "-1";
    for(int i=0;i<idList.size();i++)
    {
        if(idList.at(i)->num == num)
        {
            id = idList.at(i)->id;
        }
    }
    return id;
}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_add_clicked()
{
    //添加用户
    if(ui->id->text()!=""&&ui->password->text()!=""&&ui->name->text()!="")
    {
        //信息完整
        int adm;
        if(ui->ad->currentText()=="管理员")
        {
            adm = 0;
        }
        else {
            adm=1;
        }
        QSqlQuery query;
        QString sql = QString("insert into user(id, name, password,gro) values(%1,'%2','%3',%4);")
                .arg(ui->id->text()).arg(ui->name->text()).arg(ui->password->text())
                .arg(adm);
        if(query.exec(sql))
        {
            QMessageBox::warning(this,QStringLiteral("提示"),QStringLiteral("添加成功"));
            ui->id->clear();
            ui->name->clear();
            ui->password->clear();
            loadInfo();

        }else{
            QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("添加失败"));
        }

    }else {
        QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("请填写完整信息"));
    }

}

void Admin::on_add_2_clicked()
{
    this->close();
}
