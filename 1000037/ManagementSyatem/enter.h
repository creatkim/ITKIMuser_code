#ifndef ENTER_H
#define ENTER_H

#include <QWidget>
#include <QFileDialog>
namespace Ui {
class Enter;
}
typedef struct{
    int id; //单号
    QString time;   //时间
    QString telephone;  //电话
    QString address;    //地址
    QString workname;   //维修师傅
    QString work;   //项目
    int retu;   //有无回访
    QString remark; //备注
    QString receipt;    //收据
    int admin;
}Order;
class Enter : public QWidget
{
    Q_OBJECT

public:
    explicit Enter(QWidget *parent = nullptr);
    ~Enter();
    int idactive;
    void outPut(Order ord);
private slots:
    void on_pushButton_clicked();

    void on_enter_clicked();

    void on_exit_clicked();

private:
    Ui::Enter *ui;
    QString path;
    int id;

};



#endif // ENTER_H
