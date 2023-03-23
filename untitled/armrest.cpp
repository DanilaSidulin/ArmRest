#include "armrest.h"
#include "./ui_armrest.h"
#include <QMessageBox>
#include <QStyle>
#include <QScrollBar>

ArmRest::ArmRest(int _codeRest, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ArmRest)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    codeRest = _codeRest;

    model = new QSqlQueryModel;

    ui->armLabel->setText(CustomersSQL().armText(codeRest) + " ресторан - АРМ");
    getInfo();

    connect(ui->findCustomerButton, SIGNAL(clicked()), this, SLOT(findCustomersByName()));
    connect(ui->customersTable, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(doubleClickHandler(const QModelIndex &)));
    connect(ui->goAddCustButton, SIGNAL(clicked()), this, SLOT(action_triggered()));
    connect(ui->deleteCustButton, SIGNAL(clicked()), this, SLOT(deleteCustButton_clicked()));
    connect(ui->changeCustButton, SIGNAL(clicked()), this, SLOT(changeCustButton_clicked()));
    connect(ui->addCustButton, SIGNAL(clicked()), this, SLOT(addCustButton_clicked()));
    connect(ui->custInfo, SIGNAL(triggered()), this, SLOT(action_triggered()));
    connect(ui->mainInfo, SIGNAL(triggered()), this, SLOT(mainInfo()));
    connect(ui->addInfo, SIGNAL(clicked()), this, SLOT(addInfo()));
}
ArmRest::~ArmRest()
{
    delete ui;
    delete model;
}

void ArmRest::findCustomersByName()
{
    QString name = ui->findCustomerLine->text();
    QSqlQuery request;

    qDebug() << name;

    request = CustomersSQL().selectByName(name, codeRest);

            model->setQuery(request);
            ui->customersTable->resizeColumnsToContents();
            ui->findCustomerLine->clear();
}


void ArmRest::action_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->goAddCustButton->close();
    ui->customersTable->setModel(model);

    currentInd = -1;
    showCustomer();
}

void ArmRest::mainInfo()
{
     ui->stackedWidget->setCurrentIndex(0);
     getInfo();
}

void ArmRest::showCustomer() {
    QSqlQuery request;

    ui->NameLine->clear();
    ui->WaiterCombo->setCurrentIndex(0);
    ui->TableNumLine->clear();

    qDebug() << currentInd;

    if (currentInd == -1) {
        request = CustomersSQL().selectC(codeRest);

        model->setQuery(request);

        ui->customersTable->resizeColumnsToContents();
        ui->goAddCustButton->close();
        ui->buttonStackedWidget->setCurrentIndex(0);

    } else {
        request = CustomersSQL().selectById(currentInd);

        ui->NameLine->setText(request.value(0).toString());
        ui->WaiterCombo->setCurrentText(request.value(1).toString());
        ui->TableNumLine->setText(request.value(2).toString());

        ui->buttonStackedWidget->setCurrentIndex(1);
        ui->goAddCustButton->show();
    }
}

void ArmRest::doubleClickHandler(const QModelIndex &ind) {
    currentInd = ui->customersTable->model()->data(ui->customersTable->model()->index(ind.row(), 0)).toInt();

    showCustomer();
}


void ArmRest::addCustButton_clicked()
{
    QString name= ui->NameLine->text();
    QString Waiter= ui->WaiterCombo->currentText();
    QString tablenum= ui->TableNumLine->text();


    if (name == NULL || Waiter == NULL || tablenum == NULL)
    {
        QMessageBox::information(this, "Добавить", "Заполните все поля!");
    } else
    {
        CustomersSQL().insert(name, Waiter, tablenum, codeRest);
        showCustomer();
    }
}


void ArmRest::changeCustButton_clicked()
{
    QString name= ui->NameLine->text();
    QString Waiter= ui->WaiterCombo->currentText();
    QString tablenum= ui->TableNumLine->text();

    if (name == NULL || Waiter == NULL || tablenum == NULL)
    {
        QMessageBox::information(this, "Изменить", "Заполните все поля!");
    } else
    {
        CustomersSQL().update(name, Waiter, tablenum, currentInd);

        currentInd = -1;
        showCustomer();
    }

}


void ArmRest::deleteCustButton_clicked()
{

    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Удалить", "Вы уверены, что хотите удалить?",
                                                               (QMessageBox::Yes | QMessageBox::No));

    if (reply == QMessageBox::Yes)
    {
        CustomersSQL().deleteC(currentInd);

        currentInd = -1;
        showCustomer();
    }
    else qDebug() << "No is clicked";
}


void ArmRest::addInfo()
{
    QString info = ui->infoText->toHtml();


    if (info == NULL)
    {
        QMessageBox::information(this, "Добавить", "Введите текст!");
    } else
    {
        CustomersSQL().insertI(info, codeRest);
        getInfo();
        ui->infoText->clear();
    }
}

void ArmRest::getInfo()
{
    ui->InfoBrowser->clear();

    QSqlQuery request = CustomersSQL().getInfo(codeRest);
    int size(0);

    while (request.next())
    {
        if (size == 0)
        ui->InfoBrowser->insertHtml("<p><b>" + request.value(1).toString()
                                    + "</b></p><p>" + request.value(0).toString() + "</p>");
        else if (size % 2 != 0)
        ui->InfoBrowser->insertHtml("<p><hr/></p><p><b>" + request.value(1).toString()
                                    + "</b></p><p>" + request.value(0).toString() + "</p>");
        else
        ui->InfoBrowser->insertHtml("<p><hr/></p><p><b>" + request.value(1).toString()
                                    + "</b></p><p>" + request.value(0).toString() + "</p>");
        size++;
    }
    qDebug() << "size: " << size;

}


