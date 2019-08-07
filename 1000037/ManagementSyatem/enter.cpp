#include "enter.h"
#include "ui_enter.h"
#include <QDebug>
#include "database.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>    //sql语句
#include <QVariantList>

Enter::Enter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Enter)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
    setFixedSize(673,685);                     // 禁止拖动窗口大小
    setWindowTitle("录入");
    ui->pushButton->show();
    ui->dateEdit->show();
    ui->lineEdittime->hide();
    ui->luru->hide();
    ui->admin->hide();
    QSqlQuery query;
    QString sql = QString("select id from ord");
    query.exec(sql);
    while(query.next())
    {
        id = query.value("id").toInt();
        qDebug()<<"目前数据库中最大单号是"<<id;
    }
}

Enter::~Enter()
{
    delete ui;
}

void Enter::on_pushButton_clicked()
{
    //上传收据
    path = QFileDialog::getOpenFileName(
                this,
                "open",
                "../",
        "repict(*.png *.jpg *pic)"
                );
    QPixmap pix(path);
    pix.scaled(QSize(660,200),Qt::KeepAspectRatio);
    ui->receipt->setPixmap(path);

}

void Enter::outPut(Order ord)
{
    ui->title->setText(QString("%1号回执单").arg(ord.id));
    ui->luru->show();
    ui->admin->show();
    ui->pushButton->hide(); //隐藏上传按钮
    ui->exit->hide();
    ui->enter->hide();
    ui->dateEdit->hide();
    qDebug()<<"line 53"<<ord.id;
    ui->lineEdittime->show();
    ui->lineEdittime->setText(ord.time);
    if(ord.retu ==1)
    {
        ui->comboBox->setCurrentIndex(0);
    }else if (ord.retu==0){
        ui->comboBox->setCurrentIndex(1);
    }
    ui->workname->setText(ord.workname);
    ui->work->setText(ord.work);
    ui->reman->setText(ord.remark);
    ui->address->setText(ord.address);
    ui->usertele->setText(ord.telephone);
    ui->admin->setText(QString("%1").arg(ord.admin));
    ui->receipt->setPixmap(ord.receipt);

}

void Enter::on_enter_clicked()
{
    //点击录入
    if(ui->dateEdit->text()!=""&&ui->workname->text()!=""&&ui->work->text()!=""&&ui->address->text()!=""&& ui->usertele->text()!="")
    {
        //信息填写完整
        id++;
        Order temp;
        temp.id = this->id;
        temp.time = ui->dateEdit->text();
       // ui->dateEdit->clear();
        if(ui->comboBox->currentText()=="有")
        {
            temp.retu = 1;
        }else if (ui->comboBox->currentText()=="无"){
            temp.retu = 0;
        }
        temp.workname = ui->workname->text();
        ui->workname->clear();
        temp.work = ui->work->text();
        ui->work->clear();
        temp.remark = ui->reman->text();
        ui->reman->clear();
        temp.address = ui->address->text();
        ui->address->clear();
        temp.telephone = ui->usertele->text();
        ui->usertele->clear();
        ui->receipt->clear();
        ui->receipt->setText(QStringLiteral("此处显示收据图片"));
        //保存收据
        QString filename = QString("%1.jpg").arg(temp.id);
        QPixmap pix(path);
        if(pix.save(filename,"JPG"))
        {
            qDebug()<<"保存成功";
        }
        temp.receipt = filename;
        //插入到数据库
        QSqlQuery query;
        QString sql = QString("insert into ord(id,time,telephone,address,workname,work,retu,remark,receipt,admin) values(%1,'%2','%3','%4','%5','%6',%7,'%8','%9',%10);")
                .arg(temp.id).arg(temp.time).arg(temp.telephone).arg(temp.address).arg(temp.workname).arg(temp.work)
                .arg(temp.retu).arg(temp.remark).arg(temp.receipt).arg(idactive);

        if(query.exec(sql))
        {
            QMessageBox::warning(this,QStringLiteral("提示"),"录入成功");
        }else {
            QMessageBox::warning(this,QStringLiteral("警告"),"录入失败");
        }

    }
    else{
        QMessageBox::warning(this,QStringLiteral("警告"),"请填写完整信息");
    }

}





void Enter::on_exit_clicked()
{
    //点击退出
    this->close();
}
