#ifndef CUSTOMERSSQL_H
#define CUSTOMERSSQL_H

#include <QMainWindow>
#include <QtSql>

//Класс для работы с таблицами БД
class CustomersSQL
{
public:
    // Конструктор по умолчанию
    CustomersSQL();
    // Деструктор по умолчанию
    ~CustomersSQL();
    // Инсерт в таблицу с посетителями
    void insert(QString name, QString Waiter, QString tablenum, int codeRest);
    // Апдейт таблицы с посетителями
    void update(QString name, QString Waiter, QString tablenum, int Id);
    // Удаление из таблицы с посетителями
    void deleteC(int Id);
    // Селект из таблицы с посетителями по ИД посетителя
    QSqlQuery selectById(int Id);
    //  Селект из таблицы с посетителями по коду ресторана
    QSqlQuery selectC(int codeRest);
    // Селект из таблицы с посетителями по фамилии
    QSqlQuery selectByName(QString name, int codeRest);
    // Селект названия ресторана для отображения на главной странице
    QString armText(int codeRest);
    // Селект информации (новостей) по ресторану либо по системе
    QSqlQuery getInfo(int codeRest);
    // Инсерт информации в таблицу
    void insertI(QString info, int codeRest);
};


#endif // CUSTOMERSSQL_H
