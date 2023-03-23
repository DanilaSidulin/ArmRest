#include "customerssql.h"

CustomersSQL::CustomersSQL(){}
CustomersSQL::~CustomersSQL(){}


void CustomersSQL::insert(QString name, QString Waiter, QString tablenum, int codeRest)
{
    QSqlQuery request;

    request.prepare(R"(INSERT INTO Customers (Name, Waiter, TableNum, CodeRest, DateOfVisit)
                       VALUES (?, (SELECT Code from D_Waiter where Name LIKE ?), ?, ?, DATE('now')))");
    request.addBindValue(QString("%1").arg(name));
    request.addBindValue(QString("%2").arg(Waiter));
    request.addBindValue(QString("%3").arg(tablenum));
    request.addBindValue(QString("%4").arg(codeRest));
    qDebug() << request.boundValues();

    request.exec();
    qDebug() << request.lastError();
}

void CustomersSQL::update(QString name, QString Waiter, QString tablenum, int Id)
{
    QSqlQuery request;

    request.prepare(R"(UPDATE Customers SET
                       Name = ?,
                       Waiter = (SELECT Code from D_Waiter where Name LIKE ?),
                       TableNum = ? WHERE id = ?)");
    request.addBindValue(QString("%1").arg(name));
    request.addBindValue(QString("%2").arg(Waiter));
    request.addBindValue(QString("%3").arg(tablenum));
    request.addBindValue(QString("%4").arg(Id));

    request.exec();
    qDebug() << request.lastError();
}

void CustomersSQL::deleteC(int Id)
{
     QSqlQuery request;

     request.prepare(R"(DELETE FROM Customers WHERE Id = ?)");
     request.addBindValue(Id);

     request.exec();
     qDebug() << request.lastError();
}

QSqlQuery CustomersSQL::selectById(int Id)
{
    QSqlQuery request;

    request.prepare(R"(SELECT c.Name as 'Имя посетителя', dt.Name as 'Официант', c.TableNum as 'Номер стола'
                FROM Customers c
                LEFT JOIN D_Waiter dt on dt.Code = c.Waiter
                WHERE c.Id = ?)");
    request.addBindValue(Id);

    qDebug() << request.exec();
    request.first();
    return request;
}

QSqlQuery CustomersSQL::selectC(int codeRest)
{
    QSqlQuery request;

    request.prepare(R"(SELECT c.id as ID, c.Name as 'Имя Посетителя', dt.Name as 'Официант', c.DateOfVisit as 'Дата Посещения', c.TableNum as 'Номер стола'
                    FROM Customers c
                    LEFT JOIN D_Rest dg on dg.Code = c.CodeRest
                    LEFT JOIN D_Waiter dt on dt.Code = c.Waiter
                    WHERE c.CodeRest = ? ORDER BY id DESC LIMIT 100)");
    request.addBindValue(QString("%1").arg(codeRest));

    qDebug() << request.exec();
    return request;
}

QSqlQuery CustomersSQL::selectByName(QString name, int codeRest)
{
    QSqlQuery request;

    request.prepare(R"(SELECT c.id as ID, c.Name as 'Имя Посетителя', dt.Name as 'Официант', c.DateOfVisit as 'Дата Посещения', c.TableNum as 'Номер стола'
                    FROM Customers c
                    LEFT JOIN D_Rest dg on dg.Code = c.CodeRest
                    LEFT JOIN D_Waiter dt on dt.Code = c.Waiter
                    WHERE c.Name LIKE ? and c.CodeRest = ?)");
    request.addBindValue(QString("%%1%").arg(name));
    request.addBindValue(QString("%2").arg(codeRest));

    if(!request.exec()) qDebug() << "Ошибка выполнения sql запроса";
    return request;
}

QString CustomersSQL::armText(int codeRest)
{
    QSqlQuery request;

    request.prepare(R"(SELECT Name FROM D_Rest where Code = ?)");
    request.addBindValue(QString("%1").arg(codeRest));

    request.exec();
    request.first();

    return request.value(0).toString();
}

QSqlQuery CustomersSQL::getInfo(int codeRest)
{

    QSqlQuery request;

    request.prepare(R"(SELECT Info, DateWrite FROM Info where CodeRest = :codeRest ORDER BY Id DESC LIMIT 10)");
    request.bindValue(":codeRest", codeRest);

    request.exec();

    qDebug() << request.lastError();
    return request;
}

void CustomersSQL::insertI(QString info, int codeRest)
{
    QSqlQuery request;

    request.prepare(R"(INSERT INTO Info (Info, DateWrite, CodeRest)
                       VALUES (?, DATE('now'), ?))");
    request.addBindValue(QString("%1").arg(info));
    request.addBindValue(QString("%2").arg(codeRest));

    request.exec();
    qDebug() << request.lastError();
}
