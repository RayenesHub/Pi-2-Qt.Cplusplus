#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include <string>
#include <event.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->insertWidget(5,&em);
    ui->stackedWidget->insertWidget(4,&p);
    ui->tableView->setModel(c.afficher());
    ui->cin_sup->setModel(c.get_id());
    ui->cin_qr->setModel(c.get_id());

    //email validator
        QRegExp email(valid_email);
        //chaine validator
        QRegExp chaine(valid_chaine);
        //date validator
        QRegExp date(valid_date);
        //email validator
        QRegExp mail(valid_email);

        //champ cin
        QIntValidator *cin_valider =new QIntValidator(0,99999999,this);
        ui->cin->setValidator(cin_valider);
        ui->num_tel->setValidator(cin_valider);
        //champ nom et prenom
        QRegExpValidator *chaine_valider =new QRegExpValidator(chaine,this);
        ui->nom->setValidator(chaine_valider);
        ui->prenom->setValidator(chaine_valider);
        //champ date
        QRegExpValidator *date_valider =new QRegExpValidator(date,this);
        ui->date->setValidator(date_valider);
        //champ email
        QRegExpValidator *email_valider =new QRegExpValidator(mail,this);
        ui->ad->setValidator(email_valider);



        int ret=a.connect_arduino();
           switch (ret) {
           case(0):qDebug()<<"arduino is available and connected to :"<<a.getarduino_port_name();
               break;
           case(1):qDebug()<<"arduino is available but not connected to :"<<a.getarduino_port_name();
               break;
           case(-1):qDebug()<<"arduino is not available";
           }
     QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(incendie()));
        ui->tab_espaces->setModel(E.afficherEspaces());
        QChartView *chartview = new QChartView(Espaces().StatEspaces(),ui->widget);
        chartview->resize(500,400);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//ons


void MainWindow::on_ajouterr_clicked()
{
    int cin=ui->cin->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString date_naissance=ui->date->text();
    int num_tel=ui->num_tel->text().toInt();
    QString adresse_email=ui->ad->text();
    QString sexe=ui->sexe->currentText();

    Client c(cin,nom,prenom,sexe,date_naissance,num_tel,adresse_email);
    bool test=c.ajouter();
    if (test) //si requete ajoutée
    {
        // refresh
        ui->tableView->setModel(c.afficher());
        ui->cin_sup->setModel(c.get_id());
        ui->cin_qr->setModel(c.get_id());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("ajout effectué\n"
                                             "click cancel to exit."), QMessageBox::Cancel);
        ui->cin->clear();
        ui->nom->clear();
        ui->prenom->clear();
        ui->date->clear();
        ui->num_tel->clear();
        ui->ad->clear();
        ui->sexe->setCurrentIndex(0);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("ajout non effectué \n"
                                          "click cancel to exit."),QMessageBox::Cancel);

}


void MainWindow::on_supprimer_clicked()
{
    int cin=ui->cin_sup->currentText().toInt();
    bool test=c.supprimer(cin);
    if (test)
    {
        // refresh
        ui->tableView->setModel(c.afficher());
        ui->cin_sup->setModel(c.get_id());
        ui->cin_qr->setModel(c.get_id());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("suppression effectué\n"
                                             "click cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("suppression non effectué \n"
                                          "click cancel to exit."),QMessageBox::Cancel);
}


void MainWindow::on_modifier_clicked()
{
    int cin=ui->cin->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString sexe=ui->sexe->currentText();
    QString date_naissance=ui->date->text();
    int num_tel=ui->num_tel->text().toInt();
    QString adresse_email=ui->ad->text();




    Client c(cin,nom,prenom,sexe,date_naissance,num_tel,adresse_email);

    bool test=c.modifier();
        if(test)
        {

            ui->tableView->setModel(c.afficher());

            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("Modification avec succes.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->cin->clear();
            ui->nom->clear();
            ui->prenom->clear();
            ui->date->clear();
            ui->num_tel->clear();
            ui->ad->clear();
            ui->sexe->setCurrentIndex(0);

    }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("Modification echoué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tri_activated()
{
        if(ui->tri->currentText()=="")
          ui->tableView->setModel(c.afficher());
        else if(ui->tri->currentText()=="nom par ordre croissant")
            ui->tableView->setModel(c.tri_nom_croissant());
        else if(ui->tri->currentText()=="nom par ordre decroissant")
            ui->tableView->setModel(c.tri_nom_decroissant());
        else if(ui->tri->currentText()=="cin par ordre croissant")
            ui->tableView->setModel(c.tri_cin_croissant());
        else if(ui->tri->currentText()=="cin par ordre decroissant")
            ui->tableView->setModel(c.tri_cin_decroissant());
        else if(ui->tri->currentText()=="prenom par ordre croissant")
            ui->tableView->setModel(c.tri_nom_croissant());
        else if(ui->tri->currentText()=="prenom par ordre decroissant")
            ui->tableView->setModel(c.tri_nom_decroissant());


}

void MainWindow::on_cin_editingFinished()
{
    int cin=ui->cin->text().toInt();
        QSqlQuery query;
        query.prepare("select * from client where cin_cl=:cin");
        query.bindValue(":cin",cin);
        if (query.exec()){
            while(query.next())
            {ui->nom->setText(query.value(1).toString());
                ui->prenom->setText(query.value(2).toString());
                ui->date->setText(query.value(3).toString());
                ui->num_tel->setText(query.value(4).toString());
                ui->ad->setText(query.value(5).toString());
                ui->sexe->setCurrentText(query.value(6).toString());}
        }
}

void MainWindow::on_rechercher_clicked()
{
    QString cin=ui->cin_aff->text();
        ui->tableView->setModel(c.rech_cin(cin));
        ui->cin_aff->clear();
}

void MainWindow::on_cin_qr_currentIndexChanged()
{
        int rech=ui->cin_qr->currentText().toInt();
         QSqlQuery query;
         query.prepare("select * from client where cin_cl=:cin");
         query.bindValue(":cin",rech);

        QString cin,nom,prenom,date,num_tel,ad,sexe;

        if(query.exec())
        {
                while (query.next())
                {
                    cin=query.value(0).toString();
                    nom=query.value(1).toString();
                    prenom=query.value(2).toString();
                    date=query.value(3).toString();
                    num_tel=query.value(4).toString();
                    ad=query.value(5).toString();
                    sexe=query.value(6).toString();
                }
         }
        QString width="350",height="350";
        QString info="Cin: "+cin+", Nom: "+nom+", Prenom: "+prenom+", Date de naissance: "+date+",Num tel: "+num_tel+", Email: "+ad+",sexe:"+sexe+" ";
        QImage qr = QZXing::encodeData(info,QZXing::EncoderFormat_QR_CODE,QSize(width.toInt(), height.toInt()),QZXing::EncodeErrorCorrectionLevel_H);
        QGraphicsScene *qrcode = new QGraphicsScene(this);
        qrcode->addPixmap( QPixmap::fromImage(qr));
        ui->qr_gv->setScene(qrcode);
}

void MainWindow::on_aff_clicked()
{
    QSqlQuery qry;
        int cin=ui->cin->text().toInt();
        qry.prepare("select * from client where cin_cl=:cin");
        qry.bindValue(":cin",cin);
        if(qry.exec())
        {
            while(qry.next())
            {
                QPixmap photo;
                QString location=qry.value(7).toString();
                photo.load(location);
                ui->pic->setPixmap(photo);
                ui->pic->setScaledContents(true);
            }
        }
}

void MainWindow::on_photo_clicked()
{
    QString picpath=QFileDialog::getOpenFileName(this,tr("Open file"),"c://","JPG File(*.jpg);;PNG File(*.png)");
        int cin=ui->cin->text().toInt();
        QSqlQuery query;
        query.prepare("update client set pic=:picpath where cin_cl=:cin");
        query.bindValue(":picpath",picpath);
        query.bindValue(":cin",cin);
        query.exec();
}

void MainWindow::on_stat_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from client where sexe='homme' ");
     int number1=model->rowCount(); //combien d personnes
     model->setQuery("select * from client where sexe='femme' ");
     int number2=model->rowCount();

     int total=number1+number2;
     QString a = QString("homme  "+QString::number((number1*100)/total,'f',2)+"%");
     QString b = QString("femme "+QString::number((number2*100)/total,'f',2)+"%");

     QPieSeries *series = new QPieSeries();
     series->append(a,number1); // te9sem charte graphique
     series->append(b,number2);

     if (number1!= 0)
     {
         QPieSlice *slice = series->slices().at(0);
         slice->setLabelVisible();
         slice->setPen(QPen());
     }
     if (number2!=0)
     {
              // Add label, explode and define brush for 2nd slice
              QPieSlice *slice1 = series->slices().at(1);
              //slice1->setExploded();
              slice1->setLabelVisible();
     }
             // Create the chart widget
             QChart *chart = new QChart();
             // Add data to chart with title and hide legend
             chart->addSeries(series);
             chart->setTitle("sexes de nos clients");
             //chart->legend()->hide();
             // Used to display the chart
             QChartView *chartView = new QChartView(chart);
             chartView->setRenderHint(QPainter::Antialiasing);
             chartView->resize(1000,500);
             chartView->show();
}

void MainWindow::on_pdf_clicked()
{
    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tableView->model()->rowCount();
                const int columnCount =ui->tableView->model()->columnCount();


                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("client")
                        <<  "</head>\n"
                        "<body bgcolor=#FDFEFE link=#5000A0>\n"
                            "<h1>liste des clients</h1>"

                            "<table border=1 cellspacing=0 cellpadding=2>\n";

                // affichage titres des colonnes
                    out << "<thead><tr bgcolor=#F5B7B1>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tableView->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // affichage du contenu
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tableView->isColumnHidden(column)) {
                                   QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";



        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);


        //QTextDocument document;
        //document.setHtml(html);
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("client.pdf");
        document->print(&printer);
}






















void MainWindow::on_clients_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}








// SEIF
void MainWindow::on_espaces_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pb_ajouter_clicked()
{
    int ID_ESPACE=ui->le_ID->text().toInt();
    int CAPACITE=ui->le_capacite->text().toInt();
    QString NOM=ui->le_nom->text();
    QString TYPE=ui->le_type->text();
    QString LIEU=ui->le_lieu->text();
    QString DATE_LOCATION=ui->le_datelocation->text();
    int PRIX_LOCATION=ui->le_prixlocation->text().toInt();
    Espaces E(ID_ESPACE,CAPACITE,NOM,TYPE,LIEU,DATE_LOCATION,PRIX_LOCATION);
    bool test=false;


    test=E.ajouterEspaces();
    qDebug() << test;
    QMessageBox msgBox;
    if (test)
        msgBox.setText("ajout avec succes");
    else msgBox.setText("echec ajout");

ui->tab_espaces->setModel(E.afficherEspaces());
    msgBox.exec();

}

void MainWindow::on_SupprimerEspaces_clicked()
{
    QString id=ui->le_ID->text();
    bool test=false;

    test=Espaces().SupprimerEspaces(id);
QMessageBox msgBox;
    if (test)
    {msgBox.setText("Suppression avec succes");
     ui->tab_espaces->setModel(E.afficherEspaces());}
        else msgBox.setText("echec Suppression");
qDebug() << test;
msgBox.exec();

}

void MainWindow::on_AjouterEspaces_clicked()
{
    int ID_ESPACE=ui->le_ID->text().toInt();
    int CAPACITE=ui->le_capacite->text().toInt();
    QString x= ui->le_ID->text();
    QString NOM=ui->le_nom->text();
    QString TYPE=ui->le_type->text();
    QString LIEU=ui->le_lieu->text();
    QString DATE_LOCATION=ui->le_datelocation->text();
    int PRIX_LOCATION=ui->le_prixlocation->text().toInt();
    Espaces E(ID_ESPACE,CAPACITE,NOM,TYPE,LIEU,DATE_LOCATION,PRIX_LOCATION);
    bool test;
    test=E.modifierEspaces(x);
    QMessageBox msgBox;
    if (test)
        msgBox.setText("Modification avec succes");
    else msgBox.setText("echec modification");

ui->tab_espaces->setModel(E.afficherEspaces());
    msgBox.exec();

}

void MainWindow::on_le_ID_editingFinished()
{
    QString id= ui->le_ID->text();
    QSqlQuery q;
    q.prepare("SELECT * FROM ESPACES where id_espace = :x");
    q.bindValue(":x",id);
    q.exec();
    q.first();
    ui->le_type->setText(q.value(1).toString());
    ui->le_nom->setText(q.value(2).toString());
    ui->le_lieu->setText(q.value(3).toString());
    ui->le_capacite->setText(q.value(4).toString());
    ui->le_datelocation->setText(q.value(6).toString());
    ui->le_prixlocation->setText(q.value(5).toString());

}

void MainWindow::on_Recherche_clicked()
{
    QString x=ui->recherche->text();
    ui->tab_espaces->setModel(Espaces().RechercheEspaces(x));
}

void MainWindow::on_AnnulerRecherche_clicked()
{
    ui->tab_espaces->setModel(E.afficherEspaces());
}

void MainWindow::on_ConfimerTrie_clicked()
{
QString x=ui->Trie->currentText();
if (x=="Prix")
    ui->tab_espaces->setModel(Espaces().Trie_Prix());
else if (x=="Type")
    ui->tab_espaces->setModel(Espaces().Trie_Type());
else if (x=="Capacité")
    ui->tab_espaces->setModel(Espaces().Trie_Capacite());
}

void MainWindow::on_Exporter_clicked()
{
    QString pdf=ui->pdf->text();
    QPixmap pix(ui->widget->size());
    QPainter painter(&pix);
    ui->widget->render(&painter);
    painter.end();
    QPrinter printer(QPrinter::HighResolution);
    printer.setOrientation(QPrinter::Landscape);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    QString Emplacement = "D:\\ " + pdf + ".pdf";

    printer.setOutputFileName(Emplacement);

    painter.begin(&printer);
    double xscale = printer.pageRect().width() / double(pix.width());
    double yscale = printer.pageRect().height() / double(pix.height());
    double scale = qMin(xscale, yscale);
   painter.translate(printer.paperRect().x() + printer.pageRect().width() / 2, // largeur
                    printer.paperRect().y() + printer.pageRect().height() / 2);
    painter.scale(scale, scale);
   painter.translate(-(ui->widget->width()) / 2, -(ui->widget->height()) / 2); // hauteur
    painter.drawPixmap(0, 0, pix);
    painter.end();
}

void MainWindow::on_Map_clicked()
{
    QString chemin="D:/build-MapTest-Desktop_Qt_5_9_9_MinGW_32bit-Debug/debug/MapTest.exe";

    QProcess *x = new QProcess(this);
qDebug()<< chemin;
    x->start(chemin);
}




void MainWindow::on_calendar_clicked()
{
    QDate datee=ui->calendar->selectedDate();
        qDebug() << datee;
        QString d= datee.toString("dd/MM/yyyy");
        qDebug() << d;
        QSqlQuery query;
        query.prepare("SELECT id_espace,nom from espaces where date_location = :date");
        query.bindValue(":date",d);
        query.exec();
        QSqlQueryModel * model=new QSqlQueryModel();


              model->setQuery(query);
              model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));

              model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
             ui->tableCalendrier1->setModel(model);




}

void MainWindow::on_tableCalendrier1_clicked(const QModelIndex &index)
{


   QString i=index.data().toString();
   QSqlQuery query;
   query.prepare("Select * from espaces where id_espace = :id");
   query.bindValue(":id",i);
   qDebug() << i;
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


        ui->tableCalendrier2->setModel(model);


}


void MainWindow::incendie()
{

    data=a.read_from_arduino();
    bool test=false;
    qDebug() << data;
    if((data=="1")&&(test==false))
    {
        QMessageBox qbox;
        qbox.setText("DANGER!!!");
        qbox.setIcon(QMessageBox::Critical);
        qbox.exec();
        ui->tabWidget->setCurrentIndex(3);
        ui->stop->setEnabled(true);
        test=true;

    }
}


void MainWindow::on_stop_clicked()
{
    QString datee;
    QSqlQuery query;

    a.write_to_arduino("7");
    E.ajouterI(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm"));
    query.prepare("Select datei from hisincendie ");
    if(query.exec())
    {
        while(query.next())
        {
            datee=query.value(0).toString();

        }

    }
    qDebug()<<datee;
    QByteArray datef(datee.toUtf8(),16)    ;
    a.write_to_arduino(datef);
      ui->stop->setEnabled(false);

}















//HAZEM

void MainWindow::on_pb_ajouter_2_clicked()
{   bool t=true;
    int id=ui->le_id->text().toInt();
    QString type=ui->comboBox->currentText();
   // QString date=ui->le_date->text();
    int nombre_inv=ui->le_nombre->text().toUInt();
    int budget=ui->le_budget->text().toUInt();
    QDate date=ui->dateedit->date();
//    QString date_string = datee.toString();
//    cout<<datee<<endl ;
//    cout<<date_string<<endl;


    if(id==0||type.isEmpty()||type.isEmpty()||nombre_inv==0||budget==0)
    {
        //ui->l_id->setText("verfier ID");
        t=false;
    }

    Event EH(id,type,date,nombre_inv,budget);
    bool test=EH.ajouter();
    if(test && t)
    {

        ui->table_event->setModel(EH.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("ajouter effectue\n"
                                                                       "ok cancel to cancel"),QMessageBox::Ok);
    }

    else if (t==false)
    {
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                      QObject::tr("verifier vos donnes dabord\n"
                                                  "ok cancel to exit"),QMessageBox::Ok);}

    else
    {QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("ajouter non effectue\n"
                                          "click cancel to exit"),QMessageBox::Cancel);}
}

void MainWindow::on_pb_supprimer_clicked()
{
    int id=ui->le_id_2->text().toInt();
    bool test=EH.supprimer(id);

    QMessageBox msgBox;
    if(test)
      {
        msgBox.setText("Supression avec succes");

        //refresh

        ui->table_event->setModel(EH.afficher());
      }
    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();
}

void MainWindow::on_pb_modifier_clicked()
{
    bool t=true;
    int id=ui->le_id->text().toInt();
    QString type=ui->comboBox->currentText();
    //QString type=ui->le_type->text();
    QDate date=ui->dateedit->date();

    int nombre_inv=ui->le_nombre->text().toUInt();
    int budget=ui->le_budget->text().toUInt();
    if(id==0||type.isEmpty()||type.isEmpty()||nombre_inv==0||budget==0)
    {
        t=false;
    }

    Event E(id,type,date,nombre_inv,budget);
    bool test=EH.update();
    if(test && t)
    {
        ui->table_event->setModel(EH.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("modification effectue\n"
                                                                       "click ok pour continuer"),QMessageBox::Ok);
    }

    else if (t==false)
    {
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                      QObject::tr("verifier vos donnes \n"
                                                  "click cancel to exit"),QMessageBox::Cancel);}

    else
    {QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("modification non effectue\n"
                                          "click cancel to exit"),QMessageBox::Cancel);}
}

void MainWindow::on_pb_verifier_clicked()
{
    int id=ui->le_id->text().toInt();
//    QString type=ui->le_type->text();

    QString type=ui->comboBox->currentText();
    //QString date=ui->le_date->text();
    int nombre_inv=ui->le_nombre->text().toUInt();
    int budget=ui->le_budget->text().toUInt();


    if(id==0)
    {
        ui->l_id->setText("verfier ID");
    }
    if(id!=0)
    {
        ui->l_id->setText("  ");
    }
    if(nombre_inv==0)
    {
        ui->l_nombre->setText("verifier le nombre");
    }
    if(budget==0)
    {
        ui->l_budget->setText("verifeir le budget ");
    }
    if(nombre_inv!=0)
    {
        ui->l_nombre->setText("  ");
    }
    if(budget!=0)
    {
        ui->l_budget->setText("  ");
    }
    if (id!=0&&nombre_inv!=0&&budget!=0)
    {
        {QMessageBox::information(nullptr,QObject::tr("not ok"),
                                  QObject::tr("verification termine\n"
                                              "click ok pour continuer"),QMessageBox::Ok);}
    }
}

void MainWindow::on_pb_chercher_clicked()
{
    int id=ui->le_chercher->text().toInt();
    QString date=ui->le_chercher->text();
    QString type=ui->le_chercher->text();


    ui->table_event->setModel(EH.chercher(id,date,type));
    if(id==0&&date.length()==0&&type.length()==0)
        EH.afficher();
}

void MainWindow::on_pb_chercher_2_clicked()
{
    QString recherche = ui->le_chercher->text();
        if(recherche.length()!=0)

         {
            ui->table_event->setModel(EH.cherchertype(recherche));

         }
        else
        {
           ui->table_event->setModel(EH.afficher());
        }
}

void MainWindow::on_pb_trie_id_clicked()
{
    ui->table_event->setModel(EH.trie_id());
}

void MainWindow::on_pushButton_clicked()
{
    s = new stat_combo();
    s->setWindowTitle("statistique ComboBox");
    s->choix_pie();
    s->choix_bar();
    s->show();
}

void MainWindow::on_themebox_activated()
{
    if (ui->themebox->currentIndex()==1)
    {
        ui->khalfeya->setStyleSheet("background-color:black;");
        ui->le_id->setStyleSheet("QLineEdit{border:2px,solid white;border-radius:10px;color:black;padding-left :10px;padding-right:20px;background-color: rgb(255, 255, 255);}"
                                 "QLineEdit:hover{border:3px solid black;}"
                                 "QLineEdit{border:1.5px solid rgb(115, 115, 115);background-color: white;}"
                                 "QLineEdit:focus{border: 3px solid black;}");
        ui->le_budget->setStyleSheet("QLineEdit{border:2px,solid white;border-radius:10px;color:black;padding-left :10px;padding-right:20px;background-color: rgb(255, 255, 255);}"
                                     "QLineEdit:hover{border:3px solid black;}"
                                     "QLineEdit{border:1.5px solid rgb(115, 115, 115);background-color: white;}"
                                     "QLineEdit:focus{border: 3px solid black;}");
        ui->le_nombre->setStyleSheet("QLineEdit{border:2px,solid white;border-radius:10px;color:black;padding-left :10px;padding-right:20px;background-color: rgb(255, 255, 255);}"
                                     "QLineEdit:hover{border:3px solid black;}"
                                     "QLineEdit{border:1.5px solid rgb(115, 115, 115);background-color: white;}"
                                     "QLineEdit:focus{border: 3px solid black;}");
        ui->pb_ajouter->setStyleSheet("QPushButton{background-color: rgb(91, 91, 91);color:rgb(182, 182, 182);border-radius:15px;border-bottom:3px solid black;}"
                                      "QPushButton:enabled{background-color: rgb(91, 91, 91);color: ;}"
                                      "QPushButton:pressed{background-color: rgb(52, 52, 52);color: black;}");
        ui->pb_modifier->setStyleSheet("QPushButton{background-color: rgb(91, 91, 91);color:rgb(182, 182, 182);border-radius:15px;border-bottom:3px solid black;}"
                                       "QPushButton:enabled{background-color: rgb(91, 91, 91);color: ;}"
                                       "QPushButton:pressed{background-color: rgb(52, 52, 52);color: black;}");
        ui->pb_supprimer->setStyleSheet("QPushButton{background-color: rgb(91, 91, 91);color:rgb(182, 182, 182);border-radius:15px;border-bottom:3px solid black;}"
                                        "QPushButton:enabled{background-color: rgb(91, 91, 91);color: ;}"
                                        "QPushButton:pressed{background-color: rgb(52, 52, 52);color: black;}");
        ui->pushButton_2->setStyleSheet("QPushButton{background-color: rgb(91, 91, 91);color:rgb(182, 182, 182);border-radius:15px;border-bottom:3px solid black;}"
                                        "QPushButton:enabled{background-color: rgb(91, 91, 91);color: ;}"
                                        "QPushButton:pressed{background-color: rgb(52, 52, 52);color: black;}");
        ui->pb_verifier->setStyleSheet("QPushButton{background-color: rgb(91, 91, 91);color:rgb(182, 182, 182);border-radius:15px;border-bottom:3px solid black;}"
                                       "QPushButton:enabled{background-color: rgb(91, 91, 91);color: ;}"
                                       "QPushButton:pressed{background-color: rgb(52, 52, 52);color: black;}");
        ui->pb_chercher->setStyleSheet("QPushButton{background-color: rgb(91, 91, 91);color:rgb(182, 182, 182);border-radius:15px;border-bottom:3px solid black;}"
                                       "QPushButton:enabled{background-color: rgb(91, 91, 91);color: ;}"
                                       "QPushButton:pressed{background-color: rgb(52, 52, 52);color: black;}");
        ui->pb_chercher_2->setStyleSheet("QPushButton{background-color: rgb(91, 91, 91);color:rgb(182, 182, 182);border-radius:15px;border-bottom:3px solid black;}"
                                         "QPushButton:enabled{background-color: rgb(91, 91, 91);color: ;}"
                                         "QPushButton:pressed{background-color: rgb(52, 52, 52);color: black;}");
        ui->pushButton->setStyleSheet("QPushButton{background-color: rgb(91, 91, 91);color:rgb(182, 182, 182);border-radius:15px;border-bottom:3px solid black;}"
                                         "QPushButton:enabled{background-color: rgb(91, 91, 91);color: ;}"
                                         "QPushButton:pressed{background-color: rgb(52, 52, 52);color: black;}");
        ui->pb_reminder->setStyleSheet("QPushButton{background-color: rgb(91, 91, 91);color:rgb(182, 182, 182);border-radius:15px;border-bottom:3px solid black;}"
                                         "QPushButton:enabled{background-color: rgb(91, 91, 91);color: ;}"
                                         "QPushButton:pressed{background-color: rgb(52, 52, 52);color: black;}");
        ui->pb_trie_id->setStyleSheet("QPushButton{background-color: rgb(91, 91, 91);color:rgb(182, 182, 182);border-radius:15px;border-bottom:3px solid black;}"
                                         "QPushButton:enabled{background-color: rgb(91, 91, 91);color: ;}"
                                         "QPushButton:pressed{background-color: rgb(52, 52, 52);color: black;}");
        ui->pdf->setStyleSheet("QPushButton{background-color: rgb(91, 91, 91);color:rgb(182, 182, 182);border-radius:15px;border-bottom:3px solid black;}"
                                         "QPushButton:enabled{background-color: rgb(91, 91, 91);color: ;}"
                                         "QPushButton:pressed{background-color: rgb(52, 52, 52);color: black;}");

        ui->groupBox_h->setStyleSheet("background-color:rgb(34,34,34);border-radius:10px;border:1px solid black;");
        ui->groupBox_h2->setStyleSheet("background-color:rgb(34,34,34);border-radius:10px;border:1px solid black;");
        ui->groupBox_h3->setStyleSheet("background-color:rgb(34,34,34);border-radius:10px;border:1px solid black;");
       // ui->groupBox_4->setStyleSheet("background-color:rgb(50,50,50);border-radius:10px;border:1px solid black;");
       //ui->label_2->setStyleSheet("background-color:rgb(50,50,50);border-radius:10px;border:1px solid black;");
    }
    if (ui->themebox->currentIndex()==0)
    {
        ui->khalfeya->setStyleSheet("background-color:transparent;");
        ui->groupBox_h->setStyleSheet("background-color:rgb(248, 246, 240);border-radius:10px;");
        ui->groupBox_h2->setStyleSheet("background-color:rgb(248, 246, 240);border-radius:10px;");
        ui->groupBox_h3->setStyleSheet("background-color:rgb(248, 246, 240);border-radius:10px;");

        ui->pb_ajouter->setStyleSheet("QPushButton{background-color: rgb(93, 93, 93);color:black ;border-radius:10px;border-bottom:3px solid #aaaaaa;}"
                                      "QPushButton:enabled{background-color: rgb(230, 180, 200)  ; border-color:black;}"
                                      "QPushButton:pressed{background-color: rgb(230, 150, 180)   ;color:  black   ;}");
        ui->pb_modifier->setStyleSheet("QPushButton{background-color: rgb(93, 93, 93);color:black ;border-radius:10px;border-bottom:3px solid #aaaaaa;}"
                                      "QPushButton:enabled{background-color: rgb(230, 180, 200)  ; border-color:black;}"
                                      "QPushButton:pressed{background-color: rgb(230, 150, 180)   ;color:  black   ;}");
        ui->pb_chercher->setStyleSheet("QPushButton{background-color: rgb(93, 93, 93);color:black ;border-radius:10px;border-bottom:3px solid #aaaaaa;}"
                                      "QPushButton:enabled{background-color: rgb(230, 180, 200)  ; border-color:black;}"
                                      "QPushButton:pressed{background-color: rgb(230, 150, 180)   ;color:  black   ;}");
        ui->pb_supprimer->setStyleSheet("QPushButton{background-color: rgb(93, 93, 93);color:black ;border-radius:10px;border-bottom:3px solid #aaaaaa;}"
                                      "QPushButton:enabled{background-color: rgb(230, 180, 200)  ; border-color:black;}"
                                      "QPushButton:pressed{background-color: rgb(230, 150, 180)   ;color:  black   ;}");
        ui->pushButton_2->setStyleSheet("QPushButton{background-color: rgb(93, 93, 93);color:black ;border-radius:10px;border-bottom:3px solid #aaaaaa;}"
                                      "QPushButton:enabled{background-color: rgb(230, 180, 200)  ; border-color:black;}"
                                      "QPushButton:pressed{background-color: rgb(230, 150, 180)   ;color:  black   ;}");
        ui->pb_chercher_2->setStyleSheet("QPushButton{background-color: rgb(93, 93, 93);color:black ;border-radius:10px;border-bottom:3px solid #aaaaaa;}"
                                      "QPushButton:enabled{background-color: rgb(230, 180, 200)  ; border-color:black;}"
                                      "QPushButton:pressed{background-color: rgb(230, 150, 180)   ;color:  black   ;}");
        ui->pushButton->setStyleSheet("QPushButton{background-color: rgb(93, 93, 93);color:black ;border-radius:10px;border-bottom:3px solid #aaaaaa;}"
                                      "QPushButton:enabled{background-color: rgb(230, 180, 200)  ; border-color:black;}"
                                      "QPushButton:pressed{background-color: rgb(230, 150, 180)   ;color:  black   ;}");
        ui->pb_reminder->setStyleSheet("QPushButton{background-color: rgb(93, 93, 93);color:black ;border-radius:10px;border-bottom:3px solid #aaaaaa;}"
                                      "QPushButton:enabled{background-color: rgb(230, 180, 200)  ; border-color:black;}"
                                      "QPushButton:pressed{background-color: rgb(230, 150, 180)   ;color:  black   ;}");
        ui->pb_trie_id->setStyleSheet("QPushButton{background-color: rgb(93, 93, 93);color:black ;border-radius:10px;border-bottom:3px solid #aaaaaa;}"
                                      "QPushButton:enabled{background-color: rgb(230, 180, 200)  ; border-color:black;}"
                                      "QPushButton:pressed{background-color: rgb(230, 150, 180)   ;color:  black   ;}");
        ui->pdf->setStyleSheet("QPushButton{background-color: rgb(93, 93, 93);color:black ;border-radius:10px;border-bottom:3px solid #aaaaaa;}"
                                      "QPushButton:enabled{background-color: rgb(230, 180, 200)  ; border-color:black;}"
                                      "QPushButton:pressed{background-color: rgb(230, 150, 180)   ;color:  black   ;}");
        ui->pb_verifier->setStyleSheet("QPushButton{background-color: rgb(93, 93, 93);color:black ;border-radius:10px;border-bottom:3px solid #aaaaaa;}"
                                      "QPushButton:enabled{background-color: rgb(230, 180, 200)  ; border-color:black;}"
                                      "QPushButton:pressed{background-color: rgb(230, 150, 180)   ;color:  black   ;}");
    }

}

void MainWindow::on_langue_activated()
{

        if(ui->langue->currentIndex()==1)
        {
            ui->le_id->setPlaceholderText("  Identify");
            ui->le_budget->setPlaceholderText("  Budget of event");
            ui->le_nombre->setPlaceholderText("  Number of invited people");
            ui->pb_ajouter->setText("Add");
            ui->pb_modifier->setText("Modify");
            ui->pb_supprimer->setText("Delete");
            ui->pb_chercher->setText("Scan");
            ui->pushButton_2->setText("Sort by NB_inv");
            ui->pushButton->setText("Statistic");
            ui->pb_verifier->setText("Verify");
            ui->pb_chercher_2->setText("Display");
            ui->pb_trie_id->setText("Sort by ID");
        }
        if(ui->langue->currentIndex()==0)
        {
            ui->le_id->setPlaceholderText("  Identifiant");
            ui->le_budget->setPlaceholderText("  Budget");
            ui->le_nombre->setPlaceholderText("  Nombre des invites");
            ui->pb_ajouter->setText("Ajouter");
            ui->pb_modifier->setText("Modifier");
            ui->pb_supprimer->setText("Supprimer");
            ui->pb_chercher->setText("Recherche");
            ui->pushButton_2->setText("Tri par NB_vg");
            ui->pushButton->setText("Statistique");
            ui->pb_verifier->setText("Verifier");
            ui->pb_chercher_2->setText("Affciher");
            ui->pb_trie_id->setText("Trie par ID");

        }


}

//void MainWindow::on_pb_reminder_clicked()
//{
//    p = new Window();
//    p->show();
//}

void MainWindow::on_pb_pdf_clicked()
{
    EH.pdfprinter();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->table_event->setModel(EH.trie_nbr());
}




void MainWindow::on_eves_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}




void MainWindow::on_emplyes_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_fournisseurs_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}











