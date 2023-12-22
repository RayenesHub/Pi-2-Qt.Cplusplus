#ifndef EMPLOYES_P_H
#define EMPLOYES_P_H

#include <QWidget>
#include <EMPLOYES.h>
#include <QMainWindow>
#include "smtp.h"


namespace Ui {
class EMPLOYES_P;
}

class EMPLOYES_P : public QWidget
{
    Q_OBJECT

public:
    explicit EMPLOYES_P(QWidget *parent = nullptr);
    ~EMPLOYES_P();
     void  sendMail();

private slots:
    void on_sendboot_clicked();

    void on_pb_AJOUTER_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);




    void on_pushButton_3_clicked();

    void on_login_clicked();

    void on_sendBtn_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_comboBox_currentTextChanged(const QString &arg1);
    void  browse();

    void   mailSent(QString );




    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_activated(int index);

private:
    Ui::EMPLOYES_P *ui;
    EMPLOYES E,E1;
    QStringList files;
    QByteArray data;
};

#endif // EMPLOYES_P_H
