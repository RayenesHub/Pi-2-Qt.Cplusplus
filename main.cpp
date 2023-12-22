#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
   bool test=c.createconnect();
    MainWindow w;
    if (test)
    {
        w.show();
        QMessageBox::information(nullptr,QObject::tr("data is open"),QObject::tr("connection succeful.\n"
                                                                                  "Click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("database is not open"),QObject::tr("Connection failed. \n"
                                                                                      "Click cancel to exit."),QMessageBox::Cancel);
    return a.exec();
}
