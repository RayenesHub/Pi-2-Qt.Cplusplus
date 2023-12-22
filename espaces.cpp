#include "espaces.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
Espaces::Espaces()
{
ID_ESPACE=0;
CAPACITE=0;
NOM=" ";
TYPE=" ";
LIEU=" ";
DATE_LOCATION=" ";
PRIX_LOCATION=0;
}
Espaces::Espaces(int ID_ESPACE,int CAPACITE,QString NOM,QString TYPE,QString LIEU,QString DATE_LOCATION,float PRIX_LOCATION)
{
    this->ID_ESPACE=ID_ESPACE;
    this->CAPACITE=CAPACITE;
    this->NOM=NOM;
    this->TYPE=TYPE;
    this->LIEU=LIEU;
    this->DATE_LOCATION=DATE_LOCATION;
    this->PRIX_LOCATION=PRIX_LOCATION;
}
void Espaces::ajouterI(QString dateI){
    QSqlQuery query;
          query.prepare("INSERT INTO hisincendie (datei)"
                        "VALUES (:datei)");

          query.bindValue(":datei", dateI);


           query.exec();
}
bool Espaces::ajouterEspaces()
{


    QSqlQuery query;
          query.prepare("INSERT INTO ESPACES (ID_ESPACE,TYPE, NOM, LIEU, CAPACITE, PRIX_LOCATION, DATE_LOCATION)"
                        "VALUES (:ID_ESPACE, :TYPE, :NOM, :LIEU, :CAPACITE, :PRIX_LOCATION,:DATE_LOCATION)");
          query.bindValue(":ID_ESPACE", ID_ESPACE);
          query.bindValue(":TYPE", TYPE);
          query.bindValue(":NOM", NOM);
           query.bindValue(":LIEU", LIEU);
          query.bindValue(":CAPACITE", CAPACITE);
           query.bindValue(":PRIX_LOCATION", PRIX_LOCATION);
          query.bindValue(":DATE_LOCATION", DATE_LOCATION);


          return query.exec();
}

QSqlQueryModel * Espaces::afficherEspaces()
{
    QSqlQueryModel * model=new QSqlQueryModel();


          model->setQuery("SELECT *FROM Espaces");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Lieu"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Capacite"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Prix De Location"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date De Location"));



    return model;
}
bool Espaces::SupprimerEspaces(QString x)
{
    QSqlQuery query;
    query.prepare("Delete from espaces where id_espace = :id");
    query.bindValue(":id",x);
    return query.exec();

}
bool Espaces::modifierEspaces(QString x){
    QSqlQuery query;
          query.prepare("update espaces set type = :TYPE , nom = :NOM , lieu = :LIEU , capacite = :CAPACITE,prix_location = :PRIX_LOCATION, date_location=:DATE_LOCATION where id_espace = :x");
          query.bindValue(":x", x);
          query.bindValue(":TYPE", TYPE);
          query.bindValue(":NOM", NOM);
           query.bindValue(":LIEU", LIEU);
          query.bindValue(":CAPACITE", CAPACITE);
           query.bindValue(":PRIX_LOCATION", PRIX_LOCATION);
          query.bindValue(":DATE_LOCATION", DATE_LOCATION);


          return query.exec();






}
QSqlQueryModel * Espaces::RechercheEspaces(QString x){

    QSqlQuery query;
    query.prepare("SELECT *FROM Espaces where Id_espace = :x or type = :x or nom = :x or capacite = :x or lieu = :x or prix_location = :x or date_location = :x");
    query.bindValue(":x",x);
    query.exec();
    QSqlQueryModel * model=new QSqlQueryModel();


          model->setQuery(query);
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Lieu"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Capacite"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Prix De Location"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date De Location"));



    return model;




}
QSqlQueryModel * Espaces::Trie_Type(){

    QSqlQueryModel * model=new QSqlQueryModel();


          model->setQuery("SELECT * FROM ESPACES ORDER BY type");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Lieu"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Capacite"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Prix De Location"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date De Location"));



    return model;






}
QSqlQueryModel * Espaces::Trie_Capacite(){

    QSqlQueryModel * model=new QSqlQueryModel();


          model->setQuery("SELECT * FROM ESPACES ORDER BY Cast (capacite as int)");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Lieu"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Capacite"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Prix De Location"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date De Location"));



    return model;






}
QSqlQueryModel * Espaces::Trie_Prix(){

    QSqlQueryModel * model=new QSqlQueryModel();


          model->setQuery("SELECT * FROM ESPACES ORDER BY Cast (prix_location as int)");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Lieu"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Capacite"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Prix De Location"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date De Location"));



    return model;






}
QChart * Espaces::StatEspaces(){

    QSqlQuery query,query1,query2,query3;
    query.exec("Select * from espaces");
    int total=0;
    while (query.next())
        total++;
    query1.prepare("Select * from espaces where capacite < 500 ");
    query1.exec();

    int low_capacite=0;
    while (query1.next())
        low_capacite++;

    qreal pour_low=(low_capacite*100)/total;

    query2.prepare("Select * from espaces where capacite > 500 and capacite < 1000");

    query2.exec();
    int Medium_capacite=0;
    while (query2.next())
        Medium_capacite++;

    qreal pour_Medium=(Medium_capacite*100)/total;


    query3.prepare("Select * from espaces where capacite > 500 and capacite > 1000");

    query3.exec();
    int high_capacite=0;
    while (query3.next())
        high_capacite++;

    qreal pour_high=(high_capacite*100)/total;


    QPieSeries *series = new QPieSeries();
     series->append("0-500",pour_low);
     series->append("500-1000",pour_Medium);
     series->append("+1000",pour_high);
     QPieSlice *slice0= series->slices().at(0);
     slice0->setLabelVisible();
     QPieSlice *slice1 = series->slices().at(1);
     slice1->setLabelVisible();
     slice1->setBrush(Qt::green);
     QPieSlice *slice2 = series->slices().at(2);
     slice2->setLabelVisible();
     slice2->setBrush(Qt::red);
     QChart *chart = new QChart();
     chart->addSeries(series);
     chart->setTitle("Capacite des espaces");



    return chart;








}
