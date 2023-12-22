#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class fournisseur
{
public:
    fournisseur();
    fournisseur(QString NOM,QString PRENOM ,int CIN, QString PRODUIT,int STOCK);
    int getCIN();
    int getSTOCK();
    QString getNOM();
    QString getPRENOM();
    QString getPRODUIT();

     void expxcl();

    


    void setCIN(int);
    void setNOM(QString);
    void setPRENOM(QString);
    void setPRODUIT(QString);
    void setSTOCK(int);


    //fonctionnalites de base relatives a l'entite fournisseur
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int NCIN);

    
    void genererPDFact();
         QSqlQueryModel* Recherchefournisseur(QString);
         QSqlQueryModel * tri_cincroissant();
         bool ajouterMessage(QString);
         QSqlQueryModel * afficherMessage();


private:
      int CIN;
      int STOCK;

      QString NOM;
      QString PRENOM;
      QString PRODUIT;



};
#endif // FOURNISSEUR_H
