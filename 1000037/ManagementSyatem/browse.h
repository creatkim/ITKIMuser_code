#ifndef BROWSE_H
#define BROWSE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QPushButton>
#include <QList>

typedef struct{
   int num;
   int id;
}ID;
namespace Ui {
class Browse;
}

class Browse : public QWidget
{
    Q_OBJECT

public:
    explicit Browse(int gro,QWidget *parent = nullptr);
    ~Browse();
    int landInfo();    //加载订单
    int numToId(int num);
    int quanx;
private slots:
    void on_pushButton_clicked();

private:
    Ui::Browse *ui;
    QStandardItemModel *standItemModel;
    //QList <QPushButton *>ButtonList;
    QList <ID * >idList;

};

#endif // BROWSE_H
