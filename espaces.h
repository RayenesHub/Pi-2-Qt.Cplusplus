#ifndef ESPACES_H
#define ESPACES_H
#include <QSqlQueryModel>
#include <QString>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QDebug>
#include <qdebug.h>
QT_CHARTS_USE_NAMESPACE
class Espaces
{
public:
    Espaces();
    Espaces(int,int,QString,QString,QString,QString,float);
            int GetID_ESPACE() { return ID_ESPACE; }
            int getCAPACITE() { return CAPACITE; }
            QString GetNOM() { return NOM; }
            QString GetTYPE() { return TYPE; }
            QString GetLIEU() { return LIEU; }
            float GetPRIX_LOCATION() { return PRIX_LOCATION; }
            QString GetDATE_LOCATION() { return DATE_LOCATION; }

void ajouterI(QString);
            void setID_ESPACE(int val) { ID_ESPACE = val; }
            void setCAPACITE(int val) { CAPACITE = val; }
            void SetNOM(QString val) { NOM = val; }
            void SetTYPE(QString val) { TYPE = val; }
            void SetLIEU(QString val) { LIEU = val; }
            void SetPRIX_LOCATION(float val) { PRIX_LOCATION = val; }
            void SetDATE_LOCATION(QString val) { DATE_LOCATION = val; }

            bool ajouterEspaces();
            QSqlQueryModel * afficherEspaces();
              bool SupprimerEspaces(QString x);
              bool modifierEspaces(QString x);
         QSqlQueryModel * RechercheEspaces(QString x);
         QSqlQueryModel * Trie_Type();
         QSqlQueryModel * Trie_Prix();
         QSqlQueryModel * Trie_Capacite();
         QChart * StatEspaces();
private:
    int ID_ESPACE,CAPACITE;
    QString TYPE,NOM,LIEU,DATE_LOCATION;
    int PRIX_LOCATION;

};

#endif // ESPACES_H
