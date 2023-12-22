#ifndef CLIENT_H
#define CLIENT_H
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QString>

class Client
{
    QString nom,prenom,sexe,date_naissance,adresse_email;
    int cin,num_tel;
public:
    //ctors
    Client(){};
    Client(int,QString,QString,QString,QString,int,QString);
    //getters
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    int getCIN(){return cin;}
    QString getDate_naissance(){return date_naissance;}
    int getNum_tel(){return num_tel;}
    QString getAdresse_email(){return adresse_email;}

    //setters
    void setNom(QString n){nom=n;}
    void setPrenom(QString p){prenom=p;}
    void setCIN(int cin){this->cin=cin;}
    void set(QString n){nom=n;}
    void setDate_naissance(QString dn){date_naissance=dn;}
    void setNum_tel(int num_tel){this->num_tel=num_tel;}
    void setAdresse_email(QString am){adresse_email=am;}

    //fonctionnalites de base relatives a client
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * tri_nom_croissant();
    QSqlQueryModel * tri_nom_decroissant();
    QSqlQueryModel * tri_prenom_croissant();
    QSqlQueryModel * tri_prenom_decroissant();
    QSqlQueryModel * tri_cin_croissant();
    QSqlQueryModel * tri_cin_decroissant();
    QSqlQueryModel * rech_cin(QString);
    QSqlQueryModel * get_id();

};

#endif // CLIENT_H
