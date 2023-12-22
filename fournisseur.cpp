#include "fournisseur.h"
#include<QSqlQuery>
#include<QDebug>
#include <QSqlQueryModel>
#include <QObject>
#include<QPainter>
#include<QPdfWriter>
#include "ExcelExportHelper.h"
fournisseur::fournisseur()
{
 CIN=0;
 STOCK=0;

 NOM="";
 PRENOM="";
 PRODUIT="";


}

fournisseur::fournisseur(QString NOM,QString PRENOM ,int CIN, QString PRODUIT,int STOCK )
{
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->CIN=CIN;
    this->PRODUIT=PRODUIT;
    this->STOCK=STOCK;


}
int fournisseur::getCIN(){return  CIN;}
QString fournisseur::getNOM(){return NOM;}
QString fournisseur::getPRENOM(){return PRENOM;}
QString fournisseur::getPRODUIT(){return PRODUIT;}
int fournisseur::getSTOCK(){return STOCK;}
void fournisseur:: setCIN(int CIN){this->CIN=CIN;}
void fournisseur::setNOM(QString NOM){this->NOM=NOM;}
void fournisseur::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void fournisseur::setPRODUIT(QString PRODUIT){this->PRODUIT=PRODUIT;}
void fournisseur::setSTOCK(int STOCK){this->STOCK=STOCK;}

bool fournisseur::ajouter(){
    QSqlQuery query;
    QString CIN_string=QString::number(CIN);
    QString ST_string=QString::number(STOCK);


                              query.prepare("insert into FOURNISSEUR (NOM,PRENOM,CIN,PRODUIT,STOCK) "
                                            "values (:NOM,:PRENOM,:CIN,:PRODUIT,:STOCK)");
                              query.bindValue(":NOM", NOM);
                              query.bindValue(":PRENOM", PRENOM );
                              query.bindValue(":CIN", CIN_string);
                              query.bindValue(":PRODUIT", PRODUIT);
                              query.bindValue(":STOCK", ST_string);


                              return query.exec();  //retrun TRUE OR FALSE

}

bool fournisseur::supprimer(int CIN)
{
   QSqlQuery query;
   query.prepare("Delete from FOURNISSEUR where CIN=:CIN");
   query.bindValue(0,CIN);
           return  query.exec();
}


QSqlQueryModel *fournisseur::afficher()
{
QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("SELECT * FROM FOURNISSEUR");//afficher la total de mon table




return model;
}
bool fournisseur::modifier(int NCIN){
    QSqlQuery query;
    QString CIN_string=QString::number(CIN);
    QString ST_string=QString::number(STOCK);


                              query.prepare("UPDATE FOURNISSEUR SET NOM=:NOM,PRENOM=:PRENOM,CIN=:CIN,PRODUIT=:PRODUIT,STOCK=:STOCK WHERE CIN=:NCIN");

                              query.bindValue(":NOM", NOM);
                              query.bindValue(":PRENOM", PRENOM );
                              query.bindValue(":CIN", CIN_string);
                              query.bindValue(":PRODUIT", PRODUIT);
                              query.bindValue(":STOCK", ST_string);

     query.bindValue(":NCIN", NCIN);





    return query.exec();  //retrun TRUE OR FALSE
}




void fournisseur::genererPDFact()
{
   

    QPdfWriter pdf("C:/Users/Chelly Emna/Desktop/Atelier_Connexion/PDF.pdf");
    QPainter painter(&pdf);
   int i = 4000;
        painter.setPen(Qt::green);
        painter.setFont(QFont("Arial", 50));
        painter.drawText(1100,1200,"Liste Des fournisseur");
        painter.setPen(Qt::red);
        painter.setFont(QFont("Arial", 15));
        painter.drawRect(100,100,7300,2600);
        painter.drawRect(0,3000,9600,500);
        painter.setFont(QFont("Arial", 9));
        painter.drawText(200,3300,"NOM");
        painter.drawText(1300,3300,"PRENOM");
        painter.drawText(2400,3300,"CIN");
           painter.drawText(3500,3300,"PRODUIT");
              painter.drawText(4600,3300,"STOCK");

        QSqlQuery query;
        query.prepare("select * from GESTIONFOURNISSEUR");
        query.exec();
        while (query.next())
        {
            painter.drawText(200,i,query.value(0).toString());
            painter.drawText(1300,i,query.value(1).toString());
            painter.drawText(2400,i,query.value(2).toString());
            painter.drawText(3500,i,query.value(3).toString());
            painter.drawText(4600,i,query.value(4).toString());


           i = i + 500;
        }


}




QSqlQueryModel* fournisseur::Recherchefournisseur(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM FOURNISSEUR WHERE CIN LIKE '"+recherche+"%' OR NOM LIKE '"+recherche+"%' OR PRENOM LIKE '"+recherche+"%'");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("CIN"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRODUIT"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("STOCK"));

return model;
}



QSqlQueryModel * fournisseur::tri_cincroissant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM FOURNISSEUR ORDER BY CIN ASC ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("PRENOM"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("CIN"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRODUIT"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("STOCK"));


    return model;
}


bool fournisseur::ajouterMessage(QString nom )
   {
       QSqlQuery query;
       query.prepare("UPDATE FOURNISSEUR SET PRODUIT=:PRODUIT WHERE NOM LIKE :nom");
       query.bindValue(":NOM",nom);
       query.bindValue(":PRODUIT",PRODUIT);
       return query.exec();
   }

   QSqlQueryModel * fournisseur::afficherMessage(){
       QSqlQueryModel *model=new QSqlQueryModel();
       model->setQuery("SELECT NOM , PRODUIT FROM FOURNISSEUR where PRODUIT IS NOT NULL ");


       return model;

   }


void fournisseur::expxcl(){
        const QString fileName = "C:\\Users\\Chelly Emna\\Desktop\\Atelier_Connexion\\kaka2.xlsx";

        ExcelExportHelper helper;



    QSqlQuery query;
    query.prepare("select * from GESTIONFOURNISSEUR");
    query.exec();
    int i = 1;
    while (query.next())
    {
        helper.SetCellValue(i,1,query.value(0).toString());
        helper.SetCellValue(i,2,query.value(1).toString());
        helper.SetCellValue(i,3,query.value(2).toString());
        helper.SetCellValue(i,4,query.value(3).toString());
        helper.SetCellValue(i,5,query.value(4).toString());

       i = i +1;
    }

    helper.SaveAs(fileName);

}

