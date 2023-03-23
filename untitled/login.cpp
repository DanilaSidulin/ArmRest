#include <QMessageBox>
#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/User/Documents/untitled/databasenew.db");
    if(!mydb.open())
        qDebug()<< "Failed to open the db";
    else
        qDebug()<< "Connected...";

    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(loginButton_clicked()));
}

Login::~Login()
{
    delete ui;
}

void Login::loginButton_clicked()
{
    QString login = ui->loginLine->text();
    QString password = ui->passwordLine->text();

     qDebug() << login << password;


     if (login == NULL || password == NULL){
        QMessageBox::information(this, "Вход", "Введите логин и пароль");
    }
    else{
        QSqlQuery request;
        request.prepare("SELECT Code_Rest FROM D_User where Login = '"+login+"' and Password = '"+password+"'");
        if(!request.exec()) qDebug() << "Ошибка выполнения sql запроса";
        if (request.next()) {
            QMessageBox::information(this, "Вход", "Вы можете работать");
            close();
            qDebug() << request.value(0).toInt();
            arm = new ArmRest(request.value(0).toInt(), this);
            arm->setWindowTitle("АРМ");
            arm->show();
        }
        else {
            QMessageBox::information(this, "Вход", "Неправильный логин или пароль");
        }
    }
}

