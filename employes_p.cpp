#include "employes_p.h"
#include "ui_employes_p.h"
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

EMPLOYES_P::EMPLOYES_P(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EMPLOYES_P)
{
    ui->setupUi(this);

    ui->le_ID_EMPLOYES->setValidator(new QIntValidator(100, 99999999, this));
    ui->tableView->setModel(E.afficher());
}

EMPLOYES_P::~EMPLOYES_P()
{
    delete ui;
}

void EMPLOYES_P::on_pb_AJOUTER_clicked()
{
    int NUM_TEL=ui->le_NUM_TEL->text().toInt();
    QString NOM=ui->le_NOM->text();
    QString PRENOM=ui->le_PRENOM->text();
   QString ADRESSE_EMAIL=ui->le_ADRESSE_EMAIL->text();
    QString ADRESSE =ui->le_ADRESSE->text();
    QString ID_EMPLOYES=ui->le_ID_EMPLOYES->text();

   EMPLOYES E (NOM,PRENOM,ADRESSE_EMAIL,ADRESSE, NUM_TEL,ID_EMPLOYES);
   bool test;
  test=E.AJOUTER();
       QMessageBox msgBox;

       if(test)
       {msgBox.setText("ajout avec succes");
            ui->tableView->setModel(E.afficher());
       }
       else msgBox.setText("Echec d'ajout");
       msgBox.exec();
}

void EMPLOYES_P::on_pushButton_clicked()
{
    int i;
    QModelIndex index=ui->tableView->currentIndex();
i=index.row();
QModelIndex in=index.sibling(i,0);

QString val=ui->tableView->model()->data(in).toString();
    bool test=E1.supprimer(val);

QMessageBox msgBox;
    if(test)
     {msgBox.setText("Suppression avec succes.");

        ui->tableView->setModel(E1.afficher());

    }
    else
        msgBox.setText("Echec de suppression.");

    msgBox.exec();
}




void EMPLOYES_P::on_pushButton_2_clicked()
{
    int NUM_TEL=ui->mod_NUM_TEL->text().toInt();
    QString NOM=ui->mod_NOM->text();
    QString PRENOM=ui->mod_PRENOM->text();
    QString ADRESSE_EMAIL=ui->mod_ADRESSE_EMAIL->text();
    QString ADRESSE=ui->mod_ADRESSE->text();
    QString ID_EMPLOYES=ui->mod_ID_EMPLOYES->text();
    EMPLOYES E (NOM,PRENOM,ADRESSE_EMAIL,ADRESSE,NUM_TEL,ID_EMPLOYES);

    bool test=E.modifier(ID_EMPLOYES);
        if(test)
        {
            //tableView
            ui->tableView->setModel(E.afficher());
            QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("Modification avec succes.\n" "Click Close to exit."), QMessageBox::Close);
    }else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),QObject::tr("Modification echoue.\n" "Click Close to exit."), QMessageBox::Close);
}



void EMPLOYES_P::on_tableView_clicked(const QModelIndex &index)
{

        int i;
    i=index.row();
    QModelIndex in=index.sibling(i,0);
    QString val=ui->tableView->model()->data(in).toString();


        QSqlQuery qry;
        qry.prepare("select nom,prenom,adresse,adresse_Email,num_tel,id_employes from table1 where id_employes='"+val+"' " );


        if(qry.exec())
        {
            while(qry.next())
            {
                ui->mod_ID_EMPLOYES->setText(qry.value(5).toString());
                ui->mod_NOM->setText(qry.value(0).toString());
                ui->mod_PRENOM->setText(qry.value(1).toString());
                ui->mod_ADRESSE->setText(qry.value(2).toString());
                ui->mod_NUM_TEL->setText(qry.value(4).toString());
                ui->mod_ADRESSE_EMAIL->setText(qry.value(3).toString());

   }
    }}
void  EMPLOYES_P::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
void   EMPLOYES_P::sendMail()
{
    Smtp* smtp = new Smtp("yosra.challekh@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("yosra.challekh@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText() );
    else
        smtp->sendMail("yosra.challekh@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   EMPLOYES_P::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}


void EMPLOYES_P::on_sendboot_clicked()
{
    QString text,space="";
    QString msg=ui->msgboot->text();
    ui->conv->appendPlainText(space);
    ui->conv->appendPlainText(msg);
    ui->conv->clear();
    QString chemin;


    if(msg=="hi"||msg=="hey"||msg=="yo"){

        text="Hello user ";

    }
    else if(msg=="hello"||msg=="hallo"||msg=="heyo"||msg=="sup")
    {


        text="hey there , how are you feeling today? ";
    }
    else if(msg=="help")
    {

        text=" what's wrong? How can i help you?";
    }
    else if(msg=="day" ||msg=="when")
    {

        text=" Oh sorry ,i have not a calendar but there's one alreadyin the event space";
    }
    else if(msg=="how are you" ||msg=="hru")
    {

        text="I'm great thank you for asking and how are you! I hope you're doing great";
    }
    else if(msg=="good" ||msg=="great"||msg=="i'm great"||msg=="i'm good"||msg=="doing great")
    {


        text="Good to hear dear employee, have a good day";
    }
    else if(msg=="how to get a qrcode" ||msg=="qrcode")
    {

        text="Go to ""client"" and click on the button ""generateQR""";
    }
    else if(msg=="how to generate a pdf" ||msg=="pdf")
    {

        text="Go to ""Afficher employe"" and click on the button ""generate""";
    }
    else if(msg=="sorry" ||msg=="excuse me")
    {

        text="Don't worry about it friend";
    }
    else if(msg=="tell me" ||msg=="talk")
    {

        text="Waht do you want to talk about mate? need help in somthing? or just company?";
    }
    else if(msg=="money" ||msg=="salary")
    {

        text="We want  money don't we? work hard until you deserve it!";
    }
    else if(msg=="bored" ||msg=="i'm bored")
    {

        text="Sorry for that , a cup of coffee would help i guess!";
    }
    else if(msg=="thanks" ||msg=="thank you")
    {

        text="You're welcome i'm alwasy at your service";
    }
    else if(msg=="fuck you" ||msg=="shit"||msg=="fuck"||msg=="damn"||msg=="stupid"||msg=="idiot")
    {

        text="How dare you!Please Do not use cursing words it can hurt others like it did to me!";
    }
    else if(msg=="you are sweet"||msg=="u're sweet" )
    {

        text="I know that but i'm only  sweet with yosr ";
    }
    else if(msg=="i love you" ||msg=="i like you")
    {

        text="i love you too, bro !";
    }
    else if(msg=="" ||msg=="?"||msg==" ")
    {

        text="What's on your mind?";
    }
    else{

        text="Sorry i didnt understant , please try again";
    }

    ui->msgboot->clear();
    ui->conv->appendPlainText(space);
    ui->conv->appendPlainText(text);
}
#include "QPdfWriter"
#include "QPainter"
void EMPLOYES_P::on_pushButton_4_clicked()
{
    QPdfWriter pdf("C:/Users/revecom/Desktop/Pdf/list_employess.pdf");

           QPainter painter(&pdf);
           int i = 4100;



                  QColor dateColor(0x4a5bcf);
                  painter.setPen(dateColor);

                  painter.setFont(QFont("Montserrat SemiBold", 11));
                  QDate cd = QDate::currentDate();
                  painter.drawText(8400,250,cd.toString("Tunis"));
                  painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

                  QColor titleColor(0x341763);
                  painter.setPen(titleColor);
                  painter.setFont(QFont("Montserrat SemiBold", 25));

                  painter.drawText(3000,2700,"Liste des employes");

                  painter.setPen(Qt::black);
                  painter.setFont(QFont("Time New Roman", 15));
                  //painter.drawRect(100,100,9400,2500);
                  painter.drawRect(100,3300,9400,500);

                  painter.setFont(QFont("Montserrat SemiBold", 10));

                  painter.drawText(500,3600,"ID");
                  painter.drawText(2000,3600,"nom");
                  painter.drawText(3300,3600,"prenom");
                   painter.drawText(4500,3600,"mail");
                   painter.drawText(5700,3600,"numero");
                  painter.drawText(7500,3600,"adresse");
                  painter.setFont(QFont("Montserrat", 10));
                  painter.drawRect(100,3300,9400,9000);

                  QSqlQuery query;
                  query.prepare("select * from table1");
                  query.exec();
                  int y=4300;
                  while (query.next())
                  {
                      painter.drawLine(100,y,9490,y);
                      y+=500;
                      painter.drawText(500,i,query.value(0).toString());
                      painter.drawText(2000,i,query.value(1).toString());
                      painter.drawText(3300,i,query.value(2).toString());
                      painter.drawText(4500,i,query.value(3).toString());
                       painter.drawText(5700,i,query.value(4).toString());
                      painter.drawText(7500,i,query.value(5).toString());

                     i = i + 500;
                  }
                  QMessageBox::information( nullptr, tr( "pdf" ), tr( "done !\n\n" ) );


    }


//trie

void EMPLOYES_P::on_comboBox_currentTextChanged(const QString &arg1)
{
    QSqlQueryModel * model= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();
    QString type=ui->comboBox->currentText();
    if (type=="Par Defaut"){
        qry->prepare("select nom,prenom,adresse,adresse_Email,num_tel,id_employes from EMPLOYES");
        qry->exec();
        model->setQuery(*qry);
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE_EMAIL"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EMPLOYES"));
        ui->tableView->setModel(model);
    }
        else if (type=="NOM"){
            qry->prepare("select nom,prenom,adresse,adresse_Email,num_tel,id_employes from EMPLOYES order by nom");
            qry->exec();
            model->setQuery(*qry);
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE_EMAIL"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EMPLOYES"));
            ui->tableView->setModel(model);

        }
        else if (type=="PRENOM"){
            qry->prepare("select nom,prenom,adresse,adresse_Email,num_tel,id_employes from EMPLOYES order by prenom");
            qry->exec();
            model->setQuery(*qry);
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE_EMAIL"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EMPLOYES"));
            ui->tableView->setModel(model);

        }
        else if (type=="ADRESSE"){
            qry->prepare("select nom,prenom,adresse,adresse_Email,num_tel,id_employes from EMPLOYES order by adresse");
            qry->exec();
            model->setQuery(*qry);
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE_EMAIL"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EMPLOYES"));
            ui->tableView->setModel(model);


        }
    else if (type=="ADRESSE_EMAIL"){
        qry->prepare("select nom,prenom,adresse,adresse_Email,num_tel,id_employes from EMPLOYES order by adresse_Email");
        qry->exec();
        model->setQuery(*qry);
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE_EMAIL"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EMPLOYES"));
        ui->tableView->setModel(model);


    }
    else if (type=="ID_EMPLOYES"){
        qry->prepare("select nom,prenom,adresse,adresse_Email,num_tel,id_employes from EMPLOYES order by id_employes");
        qry->exec();
        model->setQuery(*qry);
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE_EMAIL"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EMPLOYES"));
        ui->tableView->setModel(model);


    }

}

void EMPLOYES_P::on_lineEdit_2_textChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();
    QString text=ui->lineEdit_2->text();

    if(text.isEmpty())
    {
        ui->tableView->setModel(E.afficher());

    }
    else
    {
        qry->prepare("select nom,prenom,adresse,adresse_Email,num_tel,id_employes from table1 where (  nom LIKE'%"+text+"%' OR prenom LIKE'%"+text+"%' OR adresse LIKE'%"+text+"%'OR adresse_Email LIKE'%"+text+"%'OR num_tel LIKE'%"+text+"%' OR id_employes LIKE'%"+text+"%' ) ");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
    }


}

void EMPLOYES_P::on_pushButton_3_clicked()
{
    if(ui->code->text()=="1234"){
        data.append(E.returnName(ui->idE->text()));

       // a.write_to_arduino(data);
        data.clear();
    }
    ui->idE->setText("");
     ui->code->setText("");
}

void EMPLOYES_P::on_login_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
















