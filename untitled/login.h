#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "armrest.h"

namespace Ui {
class Login;
}

// Входной класс приложения
class Login : public QWidget
{
    Q_OBJECT

public:
    // Конструктор. Инициализирует графический интерфейс, начальные характеристики работы приложения и логику работы сигналов
    explicit Login(QWidget *parent = nullptr);
    // Деструктор
    ~Login();

private slots:
    //Проверяет логин и пароль. Переводит работу в основную программу
    void loginButton_clicked();

private:
    // Хранит указатель на объект класса для работы с графическим интерфейсом
    Ui::Login *ui;
    // Хранит объект основного класса
    ArmRest *arm;
};

#endif // LOGIN_H
