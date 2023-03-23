#ifndef ARMREST_H
#define ARMREST_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include "customerssql.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ArmRest; }
QT_END_NAMESPACE

// Главный класс приложения, инкапсулирует всю логику работы
class ArmRest : public QMainWindow
{
    Q_OBJECT

public:
    // Конструктор. Инициализирует графический интерфейс, начальные характеристики работы приложения и логику работы сигналов
    ArmRest(int _codeRest, QWidget *parent = nullptr);
    // Деструктор
    ~ArmRest();

private slots:

    // Переход в режим "Посетители"
    void action_triggered();
    // Переход на главную страницу
    void mainInfo();
    // Поиск клиента по Фамилии
    void findCustomersByName();
    // Обработка двойного нажатия на таблицы
    void doubleClickHandler(const QModelIndex &ind);
    // Добавление посетителя
    void addCustButton_clicked();
    // Изменение посетителя
    void changeCustButton_clicked();
    // Удаление посетителя
    void deleteCustButton_clicked();
    // Добавить информацию
    void addInfo();
    // Получить информацию
    void getInfo();

private:
    //  Хранит указатель на объект класса для работы с графическим интерфейсом
    Ui::ArmRest *ui;
    // Хранит указатель на модель таблицы
    QSqlQueryModel *model;
    // Хранит индекс рассматриваемого объекта (если создается новый объект = -1)
    int currentInd = -1;
    // Хранит код ресторана, к которому принадлежит администратор
    int codeRest;
    // Демонстрирует данные по всем посетителям
    void showCustomer();
};
#endif // ARMREST_H
