#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "client.h"
#include <QRegExpValidator>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QMessageBox>
#include <QApplication>
#include <QRegExpValidator>
#include <QPdfWriter>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTextDocument>
#include <QTextStream>
#include <QPixmap>
#include <QFileDialog>
#include "QZXing/QZXing.h"
#include"arduino.h"
#define valid_email "^[_a-z0-9-]+(\\.[_a-z0-9-]+)*@[a-z0-9-]+(\\.[a-z0-9-]+)*(\\.[a-z]{2,4})$"
#define valid_chaine "([A-Z][a-z]*)([\\s\\'-][A-Z][a-z]*)*"
#define valid_nombre "[0-9]+"
#define valid_date "^(0?[1-9]|[12][0-9]|3[01])[\\/\\-](0?[1-9]|1[012])[\\/\\-]\\d{4}$"
#include "espaces.h"
#include <string>
#include <event.h>
//#include <window.h>
//#include <popup.h>
#include <stat_combo.h>
#include <ui_mainwindow.h>
//#include <window.h>

#include"employes_p.h"
#include "fornisseur_p.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:

    void on_ajouterr_clicked();
    void on_supprimer_clicked();
    void on_modifier_clicked();
    void on_tri_activated();
    void on_cin_editingFinished();
    void on_rechercher_clicked();
    void on_cin_qr_currentIndexChanged();

    void on_aff_clicked();

    void on_photo_clicked();
    //void incendie();
    void on_stat_clicked();
    void on_pdf_clicked();

    void on_clients_clicked();

    void on_espaces_clicked();

    void on_Recherche_clicked();

    void on_AnnulerRecherche_clicked();

    void on_ConfimerTrie_clicked();

    void on_Map_clicked();

    void on_pb_ajouter_clicked();

    void on_AjouterEspaces_clicked();

    void on_SupprimerEspaces_clicked();

    void on_Exporter_clicked();

    void on_tableCalendrier1_clicked(const QModelIndex &index);
    void on_le_ID_editingFinished();
    void on_calendar_clicked();
    void incendie();
    void on_stop_clicked();

    void on_pb_ajouter_2_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_pb_verifier_clicked();

    void on_pb_chercher_clicked();

    void on_pb_chercher_2_clicked();

    void on_pb_trie_id_clicked();

    void on_pushButton_clicked();

    void on_themebox_activated();

    void on_langue_activated();

    //void on_pb_reminder_clicked();

    void on_pb_pdf_clicked();

    void on_pushButton_2_clicked();



    void on_eves_clicked();

    void on_emplyes_clicked();

    void on_fournisseurs_clicked();

    void on_calendar_activated(const QDate &date);

    void on_tableCalendrier1_activated(const QModelIndex &index);

    void on_calendar_clicked(const QDate &date);

    void on_tableCalendrier2_clicked(const QModelIndex &index);

    void on_qr_gv_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);

    void on_tri_activated(int index);

private:
    Ui::MainWindow *ui;
    Client c;
    Arduino a;
    Espaces E;
    QByteArray data;
    Event EH;
    stat_combo *s;
    EMPLOYES_P em;
    FORNISSEUR_P p;
    //Window *p;
    //Popup *popup;
};
#endif // MAINWINDOW_H
