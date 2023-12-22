#ifndef LOGIN_H
#define LOGIN_H
#include <QMainWindow>
#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include "connection.h"
#include "EMPLOYES.h"
#include <QSql>
#include "arduino.h"


namespace Ui {
class LOGIN;
}

class LOGIN : public QMainWindow
{
    Q_OBJECT

public:
    explicit LOGIN();
    ~LOGIN();

private slots:
   // void rechEmploy();
    //void on_pushButton_clicked();

    //void on_pushButton_2_clicked();

private:
    Ui::LOGIN *ui;
    //Arduino A;
            QByteArray data ;
};

#endif // LOGIN_H
