#ifndef EMPLOYES_H
#define EMPLOYES_H
#include <QString>
#include <QSqlQueryModel>
class EMPLOYES
{
public:
    EMPLOYES();
     EMPLOYES(QString,QString,QString,QString, int,QString);
     QString getID_EMPLOYES();
     QString getNOM();
     QString getPRENOM();
     QString getADRESSE_EMAIL();
       int getNUM_TEL();
       QString getADRESSE();
       int getsalaire();

     void setID_EMPLOYES(QString);
     void setNOM(QString);
     void setPRENOM(QString);
     void setADRESSE_EMAIL(QString);
      void setNUM_TEL(int);
      void setsalaire(int);
     void setADRESSE(QString);

     bool AJOUTER();
     QSqlQueryModel* afficher();
     bool supprimer(QString);
     bool modifier(QString ID_EMPLOYES);
     QString returnName(QString);


private:

    QString ID_EMPLOYES ;
    QString NOM;
    QString PRENOM;
    QString ADRESSE_EMAIL;
    int NUM_TEL;
    QString ADRESSE ;




};

#endif // EMPLOYES_H
