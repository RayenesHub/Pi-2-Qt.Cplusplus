#ifndef FORNISSEUR_P_H
#define FORNISSEUR_P_H

#include "fournisseur.h"

#include <QMainWindow>

#include <QMainWindow>
#include <QStackedWidget>
#include <QtGui>
#include <QMainWindow>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QPixmap>
#include <QFile>
#include <QDialog>
#include <QFileDialog>

#include <QMainWindow>
#include <string>
#include <cstring>
#include <cctype>
#include <QMessageBox>
#include <iostream>
#include <bitset>
#include <sstream>
#include <algorithm>
#include <QUrl>
#include <QSystemTrayIcon>

#include<QPropertyAnimation>
#include <QRegularExpression>
#include <QTranslator>
#include <QPixmap>
#include <QString>
#include <QDate>
#include <QPrinter>
#include<QFileDialog>
#include <QTextDocument>
#include <QWidget>
#include <QSqlQueryModel>
#include <QMessageBox>
#include "smtp.h"
#include <QPainter>

#include <QMainWindow>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QSequentialAnimationGroup>
#include <QTableWidgetItem>
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FORNISSEUR_P; }
QT_END_NAMESPACE

class FORNISSEUR_P : public QMainWindow
{
    Q_OBJECT

public:
    FORNISSEUR_P(QWidget *parent = nullptr);
    ~FORNISSEUR_P();

private slots:
    void on_AJOUTER_clicked();

    void on_SUPPRIMER_clicked();

    void on_MODIFIER_clicked();

    void on_pushButton_7_clicked();



    void on_sendBtn_clicked();
        void verif_id_arduino();

        void on_le_recherche_textChanged(const QString &arg1);

        void on_pb_envoyer_clicked();

        void on_pushButton_clicked();

        void on_pushButton_8_clicked();


        void on_xcl_clicked();

private:
    Ui::FORNISSEUR_P *ui;
    fournisseur f;
    QByteArray data; // variable contenant les données reçues
    Arduino Ar;
};
#endif // FORNISSEUR_P_H
