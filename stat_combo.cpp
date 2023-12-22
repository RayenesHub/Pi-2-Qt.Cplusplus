#include "stat_combo.h"
#include "ui_stat_combo.h"

stat_combo::stat_combo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stat_combo)
{
    ui->setupUi(this);
}

stat_combo::~stat_combo()
{
    delete ui;
}


//bar chart
void stat_combo::choix_bar()
{
QSqlQuery q1,q2,q3,q4;
qreal tot=0,c1=0,c2=0,c3=0;

q1.prepare("SELECT * FROM EVENT");
q1.exec();

q2.prepare("SELECT * FROM event WHERE budget <2500");
q2.exec();

q3.prepare("SELECT * FROM event WHERE budget between 2500 and 5000 ");
q3.exec();

q4.prepare("SELECT * FROM event WHERE budget>5000 ");
q4.exec();

while (q1.next()){tot++;}
while (q2.next()){c1++;}
while (q3.next()){c2++;}
while (q4.next()){c3++;}

c1=c1/tot;
c2=c2/tot;
c3=c3/tot;


        QBarSet *set0 = new QBarSet("Budget <2500");
        QBarSet *set1 = new QBarSet("2500<budget<5000");
        QBarSet *set2 = new QBarSet("budget>5000");

        *set0 << c1;
        *set1 << c2;
        *set2 << c3;




        QBarSeries *series = new QBarSeries();

        series->append(set0);
        series->append(set1);
        series->append(set2);



        QChart *chart = new QChart();

        chart->addSeries(series);


        QBarCategoryAxis *axis = new QBarCategoryAxis();



       chart->setAxisX(axis, series);

        QPalette pal = qApp->palette();

        pal.setColor(QPalette::Window, QRgb(0xffffff));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));

        qApp->setPalette(pal);


chartView = new QChartView(chart,ui->label_stat_2);
chartView->setRenderHint(QPainter::Antialiasing);
chartView->setMinimumSize(400,400);

chartView->show();
}

    void stat_combo::choix_pie()
    {
    QSqlQuery q1,q2,q3,q4;
    qreal tot=0,c1=0,c2=0,c3=0;

    q1.prepare("SELECT * FROM event");
    q1.exec();

    q2.prepare("SELECT * FROM event WHERE type='Mariage'");
    q2.exec();

    q3.prepare("SELECT * FROM event WHERE type='Anniversaire'");
    q3.exec();

    q4.prepare("SELECT * FROM event WHERE type='Fiancaille' ");
    q4.exec();

    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}

    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;

    QPieSeries *series = new QPieSeries();
    series->append("Mariage",c1);
    series->append("Anniversaire",c2);
    series->append("Fiancaille",c3);




    QChart *chart = new QChart();

    chart->addSeries(series);
    chart->legend()->show();


    chartView = new QChartView(chart,ui->label_stat);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(400,400);

    chartView->show();
    }


