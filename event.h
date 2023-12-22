#ifndef ETUDIANT_H
#define ETUDIANT_H

#include <QString>
#include <QSqlQueryModel>
#include <QDate>
class Event
{
public:
    Event(){};
    Event(int,QString,QDate,int,int);
    int getid();
    QString gettype();
    QDate getdate();
    int getnombre_inv();
    int getbudget();
    void setid(int);
    void settype(QString);
    void setdate(QDate);
    void setnombre_inv(int);
    void setbudget(int);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool update();
    void display();
    void controle();
    QSqlQueryModel* rechercheType();
    QSqlQueryModel* rechercheID();
    QSqlQueryModel* chercher(int id,QString type,QString budget);
    QSqlQueryModel* cherchertype(QString type);
    QSqlQueryModel* trie_nbr();
    QSqlQueryModel* trie_id();
    void pdfprinter();
    void theme();
    void reminder();
    QSqlQueryModel* currentdate();


private:
    int id,nombre_inv,budget;
    QString type;
    QDate date;



};

#endif // EVENT_H
