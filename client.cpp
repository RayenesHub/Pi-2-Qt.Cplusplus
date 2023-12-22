#include "client.h"

Client::Client(int cin,QString nom,QString prenom,QString sexe,QString date_naissance,int num_tel,QString adresse_email)
{
    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->sexe=sexe;
    this->date_naissance=date_naissance;
    this->num_tel=num_tel;
    this->adresse_email=adresse_email;
}

bool Client::ajouter()
{
    QSqlQuery query; // variable d'execution
    QString res=QString::number(cin);
    QString res1=QString::number(num_tel);
    //prend la requete en parametre pour la preparer a l'execution
    query.prepare("insert into client(cin_cl,nom,prenom,date_naissance,num_tel,adresse_email,sexe)" "values(:cin, :nom, :prenom, :date_naissance, :num_tel, :adresse_email, :sexe)");
    //creation des variables liées
    query.bindValue(":cin",res);
    query.bindValue(":nom" ,nom);
    query.bindValue(":prenom" ,prenom);
    query.bindValue(":date_naissance" ,date_naissance);
    query.bindValue(":num_tel" ,res1);
    query.bindValue(":adresse_email" ,adresse_email);
    query.bindValue(":sexe" ,sexe);



    return query.exec();
}

QSqlQueryModel * Client::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from client");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_naissance"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("num_tel"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("adresse_email"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("sexe"));

    return model;
}

bool Client::supprimer(int cin)
{
    QSqlQuery query;
    QString res=QString::number(cin);

    query.prepare("delete from client where cin_cl= :cin");
    query.bindValue(":cin",res);
    return query.exec();
}

bool Client::modifier()
{
    QSqlQuery query;
    QString res=QString::number(cin);
    QString res1=QString::number(num_tel);

    query.prepare("UPDATE  client set nom=:nom,prenom=:prenom,date_naissance=:date_naissance,num_tel=:num_tel,adresse_email=:adresse_email where cin_cl=:cin");
    query.bindValue(":cin",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":date_naissance",date_naissance);
    query.bindValue(":num_tel",num_tel);
    query.bindValue(":adresse_email",adresse_email);
    //query.bindValue(":sexe",sexe);

    return query.exec();
}

QSqlQueryModel * Client::tri_nom_croissant()
  {
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from client order by nom ASC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_naissance"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("num_tel"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("adresse_email"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("sexe"));
       return model;
  }

QSqlQueryModel * Client::tri_nom_decroissant()
  {
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from client order by nom DESC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_naissance"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("num_tel"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("adresse_email"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("sexe"));
       return model;
  }

QSqlQueryModel * Client::tri_cin_croissant()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from client order by cin_cl ASC" );

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_naissance"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("num_tel"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("adresse_email"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("sexe"));
    return model;
}

QSqlQueryModel * Client::tri_cin_decroissant()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from client order by cin_cl DESC" );

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_naissance"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("num_tel"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("adresse_email"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("sexe"));
    return model;
}

QSqlQueryModel * Client::tri_prenom_croissant()
  {
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from client order by prenom ASC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_naissance"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("num_tel"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("adresse_email"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("sexe"));
       return model;
  }

QSqlQueryModel * Client::tri_prenom_decroissant()
  {
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from client order by prenom DESC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_naissance"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("num_tel"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("adresse_email"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("sexe"));
       return model;
  }

QSqlQueryModel * Client::rech_cin(QString cin)
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from client where cin_cl LIKE '"+cin+"'");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_naissance"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("num_tel"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("adresse_email"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("sexe"));
    return model;
}


QSqlQueryModel * Client::get_id()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select cin_cl from client");
    return model;
}

