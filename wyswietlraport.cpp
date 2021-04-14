#include "wyswietlraport.h"
#include "ui_wyswietlraport.h"
#include <QSqlQueryModel>
WyswietlRaport::WyswietlRaport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WyswietlRaport)
{
    ui->setupUi(this);
}

WyswietlRaport::~WyswietlRaport()
{
    delete ui;
}

void WyswietlRaport::wyswietl(QSqlQueryModel * modal)
{
    ui->tableView->setModel(modal);
}

void WyswietlRaport::on_pushButton_clicked()
{
    emit powrot();
}
