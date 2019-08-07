#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class Admin;
}
typedef struct{
   int num;
   QString id;
}ID_;
class Admin : public QWidget
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();
    int loadInfo();
    QString numToId(int num);
    QList <ID_ * >idList;
private slots:
    void on_add_clicked();

    void on_add_2_clicked();

private:
    Ui::Admin *ui;
        QStandardItemModel *standItemModel;
};

#endif // ADMIN_H
