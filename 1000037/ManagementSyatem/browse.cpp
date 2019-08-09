#include "browse.h"
#include "ui_browse.h"
#include "database.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>    //sql语句
#include <QVariantList>
#include <QPushButton>
#include "change.h"
#include <QToolTip>
Browse::Browse(int gro,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Browse)
{
    quanx =gro;
     setFixedSize(1740,701);                     // 701禁止拖动窗口大小
    ui->setupUi(this);
    if(quanx==0)
    {
        qDebug()<<"管理员"<<quanx;

    }else {
        qDebug()<<"普通用户"<<quanx;
            //setFixedSize(1311,637);                     // 701禁止拖动窗口大小
    }
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮

    setWindowTitle("浏览");
    QSqlQuery query;
    QString sql = "create table head(id int primary key, a varchar(45),b varchar(45),c varchar(45),d varchar(45),e varchar(45),f varchar(45),g varchar(45),h varchar(45),i varchar(45),j varchar(45),k varchar(45));";

    if(query.exec(sql))
    {
        qDebug()<<"创建成功";
    }
    sql = "insert into head(id,a, b, c,d,e,f,g,h,i,j,k) values(1,'单号','时间','电话','项目','地址','维修工','电话回访','录入员','备注','收费','报价');";
    if(query.exec(sql))
    {
         qDebug()<<"插入成功";
    }

    sql = "select * from head";
    if(query.exec(sql))
    {
         qDebug()<<"查询成功";
    }
    qDebug()<<"line 48";
    standItemModel = new QStandardItemModel();
    standItemModel->setColumnCount(14);
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
        standItemModel->setHeaderData(9,Qt::Horizontal,query.value("j").toString());
        ui->j->setText(query.value("j").toString());
        standItemModel->setHeaderData(10,Qt::Horizontal,query.value("k").toString());
        ui->k->setText(query.value("k").toString());
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
    if(quanx==0)
    {
        standItemModel->setHeaderData(13,Qt::Horizontal,QStringLiteral("操作"));
    }

    standItemModel->setHeaderData(12,Qt::Horizontal,QStringLiteral("修改"));
     standItemModel->setHeaderData(11,Qt::Horizontal,QStringLiteral("标记"));
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑
    int count = landInfo();
    ui->tableView->setModel(standItemModel);    //挂载表格模型
    ui->tableView->setMouseTracking(true);
    connect(ui->tableView, SIGNAL(entered(QModelIndex)),
    this, SLOT(showToolTip(QModelIndex)));

    for(int i=0;i<count;i++)
    {
        if(quanx==0)
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
            ui->tableView->setIndexWidget(standItemModel->index(i,13),m_PushButton);    //向表格单元添加一个控件


        }

        //修改
        QPushButton *PushButton=new QPushButton;
        connect(PushButton,&QPushButton::clicked,
                [=]()
                {
                    Change *chan = new Change(this->numToId(i));
                    chan->show();
                }

                );
        PushButton->setText(QStringLiteral("修改"));
        ui->tableView->setIndexWidget(standItemModel->index(i,12),PushButton);    //向表格单元添加一个控件


        //标记




        QPushButton *m_PushButton2=new QPushButton;
        m_PushButton2->setText(QStringLiteral("点击改变"));
        QSqlQuery query;
        query.exec(QString("select color from ord where id = %1").arg(numToId(i)));
        while(query.next())
        {
            if(query.value("color").toInt()==-1)
            {
                cou[i]=-1;
            }else if(query.value("color").toInt()==0){
                cou[i]=0;
                m_PushButton2->setStyleSheet("background-color:rgb(255,0,0)");
            }else if(query.value("color").toInt()==1){
                cou[i]=1;
                m_PushButton2->setStyleSheet("background-color:rgb(0,255,0)");
            }else if(query.value("color").toInt()==2){
                cou[i]=2;
                m_PushButton2->setStyleSheet("background-color:rgb(0,0,255)");
            }
        }
        ui->tableView->setIndexWidget(standItemModel->index(i,11),m_PushButton2);    //向表格单元添加一个控件

        connect(m_PushButton2,&QPushButton::clicked,
                [=]()
                {
            QString sql;
                    qDebug()<<"点击修改"<<cou[i];
                    if(cou[i]==-1)
                    {
                         sql = QString("update ord set color = %1 where id = %2;").arg(-1).arg(numToId(i));
                        cou[i]++;
                    }
                    if(cou[i]==0)
                    {
                         m_PushButton2->setStyleSheet("background-color:rgb(255,0,0)");
                          sql = QString("update ord set color = %1 where id = %2;").arg(0).arg(numToId(i));
                          cou[i]++;
                    }
                    else if(cou[i]==1)
                    {
                         m_PushButton2->setStyleSheet("background-color:rgb(0,255,0)");
                          sql = QString("update ord set color = %1 where id = %2;").arg(1).arg(numToId(i));
                          cou[i]++;
                    }else if (cou[i]==2) {
                             m_PushButton2->setStyleSheet("background-color:rgb(0,0,255)");
                              sql = QString("update ord set color = %1 where id = %2;").arg(2).arg(numToId(i));
                             cou[i] =0;
                    }
                    QSqlQuery query;

                   query.exec(sql);





                }

                );
    }


   // standItemModel.

}

void Browse::showToolTip(const QModelIndex &index) {
if (!index.isValid()) {
qDebug() << "Invalid index";
return;
}
QToolTip::showText(QCursor::pos(), index.data().toString() + "\n");
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
     qDebug()<<"line 169";
    QSqlQuery query;
    if(query.exec("select * from ord"))
    {
        qDebug()<<"line 173查询成功";
    }

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
        qDebug()<<"line 184";
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
        QStandardItem *standItem10 = new QStandardItem(tr("%1").arg(query.value("shufei").toInt()));
        QStandardItem *standItem11 = new QStandardItem(tr("%1").arg(query.value("baojia").toInt()));
        standItemModel->setItem(i,0,standItem1);                                //表格第i行，第0列添加一项内容
        //standItemModel->setData()
        //setColor__(0,1);
        standItemModel->item(i,0)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
        standItemModel->setItem(i,1,standItem2);                                //表格第i行，第1列添加一项内容
        standItemModel->setItem(i,2,standItem3);
        standItemModel->setItem(i,3,standItem4);
        standItemModel->setItem(i,4,standItem5);
        standItemModel->setItem(i,5,standItem6);
        standItemModel->setItem(i,6,standItem7);
        standItemModel->setItem(i,7,standItem8);
        standItemModel->setItem(i,8,standItem9);
        standItemModel->setItem(i,9,standItem10);
        standItemModel->setItem(i,10,standItem11);
        qDebug()<<"line 212";



        i++;
    }
    return i;
}
Browse::~Browse()
{
    delete ui;
}
void Browse::setColor__(int i, int color)
{
    for(int j=0;j<11;j++)
    {
        standItemModel->item(0,1)->setForeground(QBrush(QColor(255, 0, 0)));
    }
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
    QString sql = QString("update head set a = '%1',b= '%2',c= '%3',d= '%4',e= '%5',f= '%6',g= '%7',h= '%8',i= '%9',j='%10',k='%11' where id = 1")
            .arg(ui->a->text()).arg(ui->b->text()).arg(ui->c->text())
                  .arg(ui->d->text()).arg(ui->e->text()).arg(ui->f->text())
                  .arg(ui->g->text()).arg(ui->h->text()).arg(ui->i->text())
            .arg(ui->j->text()).arg(ui->k->text());
    qDebug()<<sql;
    if(query.exec(sql))
    {
        QMessageBox::warning(this,QStringLiteral("提示"),QStringLiteral("修改成功\n重新打开此界面后显示"));
    }
    else{
        QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("修改失败，未知错误"));
    }
}
