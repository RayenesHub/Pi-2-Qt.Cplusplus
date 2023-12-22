#include "event.h"
#include <QSqlQuery>
#include <QtDebug>
#include <iostream>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QFlags>
#include "connection.h"
#include <chrono>
#include <thread>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QModelIndex>
#include <QVariant>
#include <QDate>





using namespace std;
//Etudiant::Etudiant()
//{
//id=0;nom="";prenom="";
//}

Event::Event(int id,QString type,QDate date,int nombre_inv,int budget)
{
    this->id=id;
    this->type=type;
    this->date=date;
    this->nombre_inv=nombre_inv;
    this->budget=budget;
}
int Event::getid()
{
    return id;
}
QString Event::gettype()
{
    return type;
}
QDate Event::getdate()
{
    return date;
}
int Event::getnombre_inv()
{
    return nombre_inv;
}
int Event::getbudget()
{
    return budget;
}
void Event::setid(int id)
{
    this->id=id;
}
void Event::settype(QString type)
{
    this->type=type;
}
void Event::setdate(QDate date)
{
    this->date=date;
}
void Event::setnombre_inv(int nombre_inv)
{
    this->nombre_inv=nombre_inv;
}



bool Event::supprimer(int id)
{
    cout<<id<<endl;
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("Delete  from Event WHERE id=:id");
    qDebug()<<query.lastError();
    query.bindValue(0,id);


    return query.exec();
}



QSqlQueryModel * Event::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Event");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE D'EVENEMENT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("NOMBRE DES INVITES"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("BUDGET"));


    return model;
}


bool Event::ajouter()
{
    QString id_string=QString::number(id);
    cout<<id<<endl;
    //QString Category=comboBox->currentText();
    QString budget_string=QString::number(budget);
    QString nombre_inv_string=QString::number(nombre_inv);
    //QDate date_string=QString::fromStdString("dd.MM.yyyy");


    QSqlQuery query;
    query.prepare("INSERT INTO Event (id,type,date_event,nombre_inv,budget)"
                  "VALUES (:id,:type,:date,:nombre_inv,:budget)");
    query.bindValue(0,id_string);
    query.bindValue(1,type);
    query.bindValue(2,date);
    query.bindValue(3,nombre_inv_string);
    query.bindValue(4,budget_string);

   return query.exec();
}
bool Event::update()
{
    QString id_string=QString::number(id);
    cout<<id<<endl;


    QSqlQuery query;
    query.prepare("UPDATE EVENT SET type=:type,date_event=:date,nombre_inv=:nombre_inv,budget=:budget WHERE id=:id_string"
                  );
    query.bindValue(0,type);
    query.bindValue(1,date);
    query.bindValue(2,nombre_inv);
    query.bindValue(3,budget);
    query.bindValue(4,id_string);

    query.exec();

    return true;

}
//void Event::controle()
//{
//    if(id==0)
//    {
//        ui->l_id->setText("verfier ID");
//    }

//}


QSqlQueryModel * Event::chercher(int id,QString date,QString type)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * from event where id like :id OR date_event like :date OR type like :type ");
    query.bindValue(":id",id);
    query.bindValue(":date",date);
    query.bindValue(":type",type);

    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE D'EVENEMENT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOMBRE DES INVITES"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("BUDHET"));


    return model;
}
QSqlQueryModel* Event::cherchertype(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM event where TYPE LIKE '"+recherche+"%'  OR LOWER(TYPE) LIKE '"+recherche+"%' OR UPPER(TYPE) LIKE '"+recherche+"%'");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("date_event"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("nombre_inv"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("budget"));
    return model;
}





QSqlQueryModel * Event::trie_nbr()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM EVENT ORDER BY nombre_inv");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE_EVENT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("NOMBRE_INV"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("BUDGET"));

    return model;
}
QSqlQueryModel * Event::trie_id()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM EVENT ORDER BY ID");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE_EVENT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("NOMBRE_INV"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("BUDGET"));
    return model;
}

//QSqlQueryModel * Event::Trier_ID_D()
//{
//    QSqlQueryModel * model=new QSqlQueryModel();
//    model->setQuery("SELECT * FROM LOGEMENT ORDER BY ID_L DESC");
//    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_L"));
//    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE_L"));
//    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRIX_L"));
//    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE_L"));
//    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MAIL_L"));
//    model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUM_TEL_L"));
//    return model;
//}
//QSqlQueryModel * Event::Trier_ID_A()
//{
//    QSqlQueryModel * model=new QSqlQueryModel();
//    model->setQuery("SELECT * FROM LOGEMENT ORDER BY ID_L ASC");
//    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_L"));
//    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE_L"));
//    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRIX_L"));
//    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE_L"));
//    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MAIL_L"));
//    model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUM_TEL_L"));
//    return model;
//}

//QSqlQueryModel * Event::Trier_adresse_A()
//{
//    QSqlQueryModel * model=new QSqlQueryModel();
//    model->setQuery("SELECT * FROM LOGEMENT ORDER BY ADRESSE_L ASC ");
//    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_L"));
//    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE_L"));
//    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRIX_L"));
//    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE_L"));
//    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MAIL_L"));
//    model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUM_TEL_L"));
//    return model;
//}
//QSqlQueryModel * Event::Trier_adresse_D()
//{
//    QSqlQueryModel * model=new QSqlQueryModel();
//    model->setQuery("SELECT * FROM LOGEMENT ORDER BY ADRESSE_L DESC ");
//    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_L"));
//    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE_L"));
//    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRIX_L"));
//    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE_L"));
//    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MAIL_L"));
//    model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUM_TEL_L"));
//    return model;
//}
//QSqlQueryModel* Event::getAllId()
//{
//    QSqlQueryModel* model=new QSqlQueryModel();

//    model->setQuery("SELECT ID_L FROM LOGEMENT");

//    return model;
//}
// bool  Event::controlTel(int tel)
// {
//     QString num= QString::number(tel);
//         for(int i=0;i<num.length();i++)
//         {
//             if (num.length()==8)
//             {
//                 return false;
//             }
//         }
//         return true;
// }
void Event::pdfprinter()
{
QPdfWriter pdf("C:/Users/a/Documents/crudddd/events.pdf");

       QPainter painter(&pdf);


      painter.setPen(Qt::red);
      painter.setFont(QFont("Arial", 50));
      painter.drawText(4000,1000,"EVENEMENT");

      painter.drawRect(3800,1200,1700,500);
      painter.drawRect(0,3000,9600,500);
      painter.setPen(Qt::red);
      painter.setFont(QFont("Arial", 11));
      painter.drawText(500,3300,"ID");
      painter.drawText(2000,3300,"TYPE");
      painter.drawText(3500,3300,"DATE");
      painter.drawText(4500,3300,"NB INVITES");
      painter.drawText(6500,3300,"BUDGET");




      QSqlQuery query;
      int i = 4000;

       query.prepare("select * from event");
       query.exec();
    while (query.next())
      {
          painter.setPen(Qt::black);
          painter.setFont(QFont("Arial", 9));
          painter.drawText(500,i,query.value(0).toString());
          painter.drawText(1800,i,query.value(1).toString());
          painter.drawText(3500,i,query.value(2).toString());
          painter.drawText(5000,i,query.value(3).toString());
          painter.drawText(6500,i,query.value(4).toString());


          i = i +500;
      }
}






