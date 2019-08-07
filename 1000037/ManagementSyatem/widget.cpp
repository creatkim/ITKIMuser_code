#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
    setFixedSize(658,464);                     // 禁止拖动窗口大小
    setWindowTitle("主界面");
    land = new LandWidget();
    land->show();
    connect(land,&LandWidget::landSucceed,
            [=]()
            {
                //当接收到登陆窗口传来的登陆成功信号时
                this->gro = land->gro;
                this->idactive = land->idactive;
                land->close();   //隐藏登陆窗口
                this->show();   //显示主窗口
                delete land;   //登陆成功后销毁登陆界面对象
            }
            );

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_enterButton_clicked()
{
    //录入
    enter = new Enter();
    enter->idactive = this->idactive;
    enter->show();
}

void Widget::on_browseButton_clicked()
{
    //浏览
    bro = new Browse(gro);

    bro->show();
}

void Widget::on_sortButton_clicked()
{
    //搜索
    sort = new Sort();
    sort->show();
    //更改录入界面标题，并传入内容
}

void Widget::on_helpButton_clicked()
{
    //管理
    if(gro == 0)
    {
        //有权限
        admin = new Admin();
        admin->show();
    }else{
        QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("您没有权限进行此操作"));
    }


}

void Widget::on_pushButton_clicked()
{
    this->close();
}
