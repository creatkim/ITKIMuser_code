#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
class DataBase
{
public:
    DataBase();
    void initDataBase();    //初始化数据库
    int dealLand(QString id,QString password);
};

#endif // DATABASE_H
