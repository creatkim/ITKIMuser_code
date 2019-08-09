#include "database.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>    //sql语句
#include <QVariantList>

DataBase::DataBase()
{
    initDataBase(); //初始化数据库

}
void DataBase::initDataBase()
{
    //从数据库中加载信息
    //打印Qt支持的数据库驱动
    qDebug()<<QSqlDatabase::drivers();

    //添加Sqlite数据库驱动
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库
    db.setDatabaseName("info.db");


    //打开数据库
    if( !db.open())
    {
        //数据库打开失败
        qDebug()<<"line 26 open fail";
        return;
    }
    QSqlQuery query;
//    query.exec("select * from ord");


//    while(query.next()) //一行一行遍历
//    {
//        //取出当前行内容
//        qDebug()<<"取";
//        qDebug()<< query.value("id").toInt()
//                << query.value("time").toString()
//                << query.value("telephone").toString()
//                << query.value("address").toString()
//                << query.value("workname").toString()
//                <<query.value("work").toString()
//               << query.value("retu").toInt()
//               <<query.value("remark").toString()
//              <<query.value("receipt").toString()
//             <<query.value("admin").toInt();
//     }

//    //query.exec("insert into user(id, name, password,gro) values(10002,'操作员','001221',1);");
//     //建表,用于开发时设计数据库，后期不需要执行

//    if(query.exec("create table user(id int primary key,name varchar(45),password varchar(45),gro int);"))
//    {
//         qDebug()<<"user jia建表成功";
//    }else {
//    qDebug()<<"line39 失败";
//    }
//    //
//    if(query.exec("create table ord(id int primary key,time varchar(20),telephone varchar(20),address varchar(100),workname varchar(100),work varchar(100),retu int,remark varchar(255),receipt varchar(255),admin int,shufei int,baojia int,color int);"))
//    {
//         qDebug()<<"ord 建表成功";
//    }else {
//    qDebug()<<"line39 失败";
//    }
//    if(query.exec("insert into user(id, name, password,gro) values(888888,'管理员','123456',0);"))
//    {
//         qDebug()<<"插入账号成功";
//    }else {
//    qDebug()<<"插入账号失败";
//    }
   // query.exec("insert into ord(id) values(0);");
//    //query.exec("");
//    //query.exec("");  //插入
//    //query.exec("");  //插入

//    //测试
//    //遍历数据库




}
int DataBase::dealLand(QString id, QString password)
{
    //处理登陆窗口发来的登陆信息，正确返回1错误返回0
    QSqlQuery query;
    QString sql = QString("select password,gro from user where id = %1").arg(id);
    query.exec(sql);
    if(password == query.value("password").toString())
    {
        //密码正确
        qDebug()<<query.value("gro").toInt();
        return query.value("gro").toInt();
    }else {
        return -1;
    }

}
