#include "fornisseur_p.h"
#include "ui_fornisseur_p.h"
#include "ExcelExportHelper.h"
#include"fournisseur.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QFileDialog>
#include "connection.h"
#include <QFile>
#include <QtDebug>
#include<QPdfWriter>
#include <QPainter>
#include <QSqlQuery>
#include<QtCharts>

#include<QPieSlice >
#include<QPieSeries>
#include<QPrinter>
#include <QFileDialog>
#include<QPrintDialog>
#include <QIntValidator>
#include <QValidator>
#include <QMessageBox>
#include <QDebug>
#include <QIntValidator>
#include <QSqlQueryModel>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include<QDesktopServices>
#include<QUrl>
#include <QTextStream>
#include <QTextDocument>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QtWidgets>
#include<QFileDialog>
#include<QGraphicsView>
#include<QPdfWriter>
#include<QSqlQuery>
#include<QSystemTrayIcon>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include<QUrlQuery>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include <QDate>
#include <QTime>
#include<QSqlTableModel>
#include<QItemSelectionModel>
#include<QTableWidgetItem>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QDateEdit>
#include <QComboBox>
#include <QPixmap>
//#include <QMediaPlayer>
#include <QTabWidget>
#include <QObject>
#include <QDialog>
#include <QValidator>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QSequentialAnimationGroup>
#include <QState>
#include <QStateMachine>
#include <QSignalTransition>
#include <QPainter>
#include<QString>
#include<QStatusBar>
#include <QSound>
#include<QTimer>
#include<QDateTime>
 #include <QApplication>
#include <QtCore>



FORNISSEUR_P::FORNISSEUR_P(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FORNISSEUR_P)
{
    ui->setupUi(this);
    ui->tab_FOURNISSEUR->setModel(f.afficher());
    ui->lineEdit_cin_S->setValidator(new QIntValidator(0,99999999,this));
       ui->lineEdit_CIN1->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_cin->setValidator(new QIntValidator(0,99999999,this));
    data="";
        int ret=Ar.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< Ar.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<Ar.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(Ar.getserial(),SIGNAL(readyRead()),this,SLOT(verif_id_arduino()));
}

FORNISSEUR_P::~FORNISSEUR_P()
{
    delete ui;
}

void FORNISSEUR_P::on_AJOUTER_clicked()
{

    QString NOM=ui->lineEdit_nom->text();
    QString PRENOM=ui->lineEdit_pr->text();
    int CIN=ui->lineEdit_cin->text().toInt();
    QString PRODUIT=ui->lineEdit_pro->text();
    int STOCK=ui->lineEdit_st->text().toInt();

           fournisseur f ( NOM,PRENOM ,CIN, PRODUIT,STOCK);

            bool test= f.ajouter();
                           if(test){
                               FORNISSEUR_P w;
                           w.show();
                           QMessageBox::information(nullptr, QObject::tr("database is open"),
                                       QObject::tr("Ajout effectué.\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);
                              ui->tab_FOURNISSEUR->setModel(f.afficher());
                       }
                       else
                           QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                       QObject::tr("Ajout non effectué.\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);

}

void FORNISSEUR_P::on_SUPPRIMER_clicked()
{
    fournisseur f1;
 f1.setCIN(ui->lineEdit_cin_S->text().toInt());

bool test=f1.supprimer(f1.getCIN());
QMessageBox msgBox;
if(test)
{

   msgBox.setText("Suppression avec succes.");
   ui->tab_FOURNISSEUR->setModel(f1.afficher());
}
else
   msgBox.setText("Echec de suppression");
msgBox.exec();


}




void FORNISSEUR_P::on_MODIFIER_clicked()
{

    QString NOM=ui->lineEdit_N_nom->text();
    QString PRENOM=ui->lineEdit_N_prenom->text();
    int CIN=ui->lineEdit_N_cin->text().toInt();
    QString PRODUIT=ui->lineEdit_N_produit->text();
    int STOCK=ui->lineEdit_N_stock->text().toInt();
    int NCIN=ui->lineEdit_CIN1->text().toInt();

           fournisseur f ( NOM,PRENOM ,CIN, PRODUIT,STOCK);

            bool test= f.modifier(NCIN);
                           if(test){
                               FORNISSEUR_P w;
                           w.show();
                           QMessageBox::information(nullptr, QObject::tr("database is open"),
                                       QObject::tr("modifier effectué.\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);
                              ui->tab_FOURNISSEUR->setModel(f.afficher());
                       }
                       else
                           QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                       QObject::tr("modification non effectué.\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);




}

void FORNISSEUR_P::on_pushButton_7_clicked()
{
    QPdfWriter pdf("C://Users//lamti//Downloads/pdf//PDF_Fournisseur.pdf");

           QPainter painter(&pdf);
           int i = 4000;
                  painter.setPen(Qt::red);
                  painter.setFont(QFont("Time New Roman", 25));
                  painter.drawText(3000,1400,"Liste Des Fournisseur");
                  painter.setPen(Qt::black);
                  painter.setFont(QFont("Time New Roman", 15));
                  painter.drawRect(100,3000,9400,500);
                  painter.setFont(QFont("Time New Roman", 9));
                  painter.drawText(1000,3300,"NOM");
                  painter.drawText(2500,3300,"PRENOM");
                  painter.drawText(4000,3300,"CIN");
                  painter.drawText(5500,3300,"PRODUIT");
                  painter.drawText(7000,3300,"STOCK");
                  painter.drawRect(100,3000,9400,9000);

                  QSqlQuery query;
                  query.prepare("select * from FOURNISSEUR");
                  query.exec();
                  while (query.next())
                  {
                      painter.drawText(1000,i,query.value(0).toString());
                      painter.drawText(2500,i,query.value(1).toString());
                      painter.drawText(4000,i,query.value(2).toString());
                      painter.drawText(5500,i,query.value(3).toString());
                      painter.drawText(7000,i,query.value(4).toString());


                     i = i + 350;
                  }
                  QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                  QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}




void FORNISSEUR_P::on_le_recherche_textChanged(const QString &arg)
{
    QString rech=ui->le_recherche->text();
    ui->tab_FOURNISSEUR->setModel(f.Recherchefournisseur(rech));
}





void FORNISSEUR_P::on_pushButton_8_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                             model->setQuery("select * from FOURNISSEUR where STOCK< 100 ");
                             float code=model->rowCount();
                             model->setQuery("select * from FOURNISSEUR where STOCK between 100 and 1000 ");
                             float codee=model->rowCount();
                             model->setQuery("select * from  FOURNISSEUR  where STOCK >1000 ");
                             float codeee=model->rowCount();
                             float total=code+codee+codeee;
                             QString a=QString("moins de 100 \t"+QString::number((code*100)/total,'f',2)+"%" );
                             QString b=QString("entre 100 et 1000 \t"+QString::number((codee*100)/total,'f',2)+"%" );
                             QString c=QString("+1000 \t"+QString::number((codeee*100)/total,'f',2)+"%" );
                             QPieSeries *series = new QPieSeries();
                             series->append(a,code);
                             series->append(b,codee);
                             series->append(c,codeee);
                     if (code!=0)
                     {QPieSlice *slice = series->slices().at(0);
                      slice->setLabelVisible();
                      slice->setPen(QPen());}
                     if ( codee!=0)
                     {
                              // Add label, explode and define brush for 2nd slice
                              QPieSlice *slice1 = series->slices().at(1);
                              //slice1->setExploded();
                              slice1->setLabelVisible();
                     }
                     if(codeee!=0)
                     {
                              // Add labels to rest of slices
                              QPieSlice *slice2 = series->slices().at(2);
                              //slice1->setExploded();
                              slice2->setLabelVisible();
                     }
                             // Create the chart widget
                             QChart *chart = new QChart();
                             // Add data to chart with title and hide legend
                             chart->addSeries(series);
                             chart->setTitle("Pourcentage Par STOCK :Nombre Des Espaces "+ QString::number(total));
                             chart->legend()->hide();
                             // Used to display the chart
                             QChartView *chartView = new QChartView(chart);
                             chartView->setRenderHint(QPainter::Antialiasing);
                             chartView->resize(1000,500);
                             chartView->show();




}


void FORNISSEUR_P::on_pushButton_clicked()
{
    fournisseur P;
       ui->tab_FOURNISSEUR->setModel(f.tri_cincroissant());

           bool test=P.tri_cincroissant();// tri produit
           if (test)
           {


               QMessageBox::information(nullptr,QObject::tr("ok"),
                                        QObject::tr("tri croissante effectué \n"
                                                    "Click Cancel to exist ."),QMessageBox::Cancel);

           }
           else
            {    QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                             QObject::tr("tri croissante failed.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);}

       }


void FORNISSEUR_P::on_pb_envoyer_clicked()
{


   fournisseur p;
   p.setNOM(ui->le_id_chat->text());
    p.setPRODUIT(ui->le_message->text());
    QMessageBox msgbox;
    bool test=p.ajouterMessage(p.getNOM());
    if(test)
    {
        msgbox.setText("un nouveau message");
        ui->tab_message->setModel(p.afficherMessage());
    }
    else
        msgbox.setText("probleme d'envoie de message");
    msgbox.exec();

}
void FORNISSEUR_P::verif_id_arduino()
{
data="";
QString a;
 data=Ar.read_from_arduino()/*[0]*/;
     a.append(data);


     if(a.length()==4)
     {qDebug()<<a;
         /*QSqlQueryModel *model=new QSqlQueryModel();
         model->setQuery("SELECT * FROM FOURNISSEUR where CIN ="+data);
         if (model->rowCount()==0){
             Ar.write_to_arduino("CIN erroné");
             qDebug()<<"CIN erroné";
         }
         else{
                 QByteArray nom = model->data(model->index(0,0)).toByteArray();
                 Ar.write_to_arduino("bonjour "+nom);

                 qDebug()<<"bonjour "<<nom;
             }

         }else
            {
             if (a=='1' || a=='2' || a=='3' || a=='4' || a=='5' || a=='6' || a=='7' || a=='8' || a=='9' )
             data+=a;}
         qDebug()<<data;*/

     } }


void FORNISSEUR_P::on_sendBtn_clicked()
{
    ui->server->setPlaceholderText("smtp.gmail.com");
    ui->port->setPlaceholderText("25");
    QString mail = ui->rcpt->text();
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());

    if(    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)))
)
    {
        QMessageBox::critical(this, "envoyer un mail", "Message non Envoyé (probleme de connexion)");
    }
    else
    {
        QMessageBox::information(this, "envoyer un mail", "Message envoyé avec succès.");
    }




}






void FORNISSEUR_P::on_xcl_clicked()
{

    const QString fileName = "C://Users//lamti//Downloads//xl//PDF_Fournisseur.xlsx";

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

}

