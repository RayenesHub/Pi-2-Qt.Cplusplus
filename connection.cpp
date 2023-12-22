#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");//test
db.setUserName("rayene");//akrem
db.setPassword("rayene");//akrem

if (db.open())
test=true;





    return  test;
}
