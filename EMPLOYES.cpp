#include "EMPLOYES.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QString>
#include <iostream>
using namespace std;

EMPLOYES::EMPLOYES()
{
NUM_TEL=0;NOM="";PRENOM="";ID_EMPLOYES="";ADRESSE_EMAIL="";ADRESSE="";
}


 EMPLOYES::EMPLOYES(QString NOM,QString PRENOM,QString ADRESSE_EMAIL,QString ADRESSE,int NUM_TEL,QString ID_EMPLOYES)
{this->NUM_TEL=NUM_TEL; this->NOM=NOM; this->PRENOM=PRENOM; this->ADRESSE_EMAIL=ADRESSE_EMAIL;this->ADRESSE=ADRESSE;this->ID_EMPLOYES=ID_EMPLOYES;}
 int EMPLOYES::getNUM_TEL(){return NUM_TEL;}
 QString EMPLOYES::getNOM(){return NOM; };
 QString EMPLOYES::getPRENOM(){return PRENOM;};
 QString EMPLOYES::getADRESSE_EMAIL(){return ADRESSE_EMAIL;};
 QString EMPLOYES::getADRESSE(){return ADRESSE;};
 QString EMPLOYES::getID_EMPLOYES(){return ID_EMPLOYES;};
 void EMPLOYES::setNUM_TEL(int NUM_TEL){this->NUM_TEL=NUM_TEL;};
 void EMPLOYES::setADRESSE_EMAIL(QString ADRESSE_EMAIL ){this->ADRESSE_EMAIL=ADRESSE_EMAIL;};
 void EMPLOYES::setADRESSE(QString ADRESSE ){this->ADRESSE=ADRESSE;};
 void EMPLOYES::setNOM (QString NOM ){this->NOM=NOM;};
 void EMPLOYES::setPRENOM(QString PRENOM ){this->PRENOM=PRENOM;};
 void EMPLOYES::setID_EMPLOYES(QString ID_EMPLOYES ){this->ID_EMPLOYES=ID_EMPLOYES;};

bool EMPLOYES::AJOUTER()
{

    QSqlQuery query;
    QString NUM_TEL_string= QString::number(NUM_TEL);
          query.prepare("INSERT INTO EMPLOYES(NUM_TEL, NOM,PRENOM,ADRESSE_EMAIL,ADRESSE,ID_EMPLOYES ) ""VALUES (:NUM_TEL, :NOM,:PRENOM,:ADRESSE_EMAIL,:ADRESSE,:ID_EMPLOYES )");
          query.bindValue(0,NUM_TEL_string );
          query.bindValue(1, NOM);
          query.bindValue(2,PRENOM );
          query.bindValue(3, ADRESSE_EMAIL);
          query.bindValue(4, ADRESSE);
          query.bindValue(5, ID_EMPLOYES);
 return query.exec();
}

QString EMPLOYES::returnName(QString idE)
{

    QSqlQuery query("select * from EMPLOYES where id_employes='"+idE+"'");
  while(query.next())
      return query.value(2).toString();
return "";
}



bool EMPLOYES::supprimer(QString ID_EMPLOYES)
{

    QSqlQuery query;
          query.prepare("Delete from EMPLOYES where ID_EMPLOYES=:ID_EMPLOYES");
          query.bindValue(":ID_EMPLOYES",ID_EMPLOYES);

 return query.exec();

}
QSqlQueryModel* EMPLOYES::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
 model->setQuery("SELECT* FROM EMPLOYES");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM_TEL"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE_EMAIL"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
 model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID_EMPLOYES"));




    return model;
}

bool EMPLOYES::modifier(QString ID_EMPLOYES){
    QSqlQuery query;
   QString NUM_TEL_string= QString::number(NUM_TEL);
    //requette sql
    query.prepare("UPDATE EMPLOYES SET  NUM_TEL=:num , NOM=:nom  , PRENOM=:prenom , ADRESSE_EMAIL=:mail ,  "
                  "ADRESSE=:adresse  where ID_EMPLOYES=:id ");
    //saisir de donnee
    query.bindValue(":id",ID_EMPLOYES);
    query.bindValue(":num",NUM_TEL_string);
    query.bindValue(":nom",NOM);
    query.bindValue(":prenom",PRENOM);
    query.bindValue(":mail",ADRESSE_EMAIL);
    query.bindValue(":adresse",ADRESSE);




    //execution de la requetteNU
    return query.exec();
}

