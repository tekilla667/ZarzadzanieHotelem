#include "listarezerwacji.h"
#include "ui_listarezerwacji.h"

listarezerwacji::listarezerwacji(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::listarezerwacji)
{
    ui->setupUi(this);
    
}

listarezerwacji::~listarezerwacji()
{
    delete ui;
}

void listarezerwacji::ustawModel(QSqlQueryModel *modal)
{
    ui->tableView->setModel(modal);
}

void listarezerwacji::on_pushButton_6_clicked()
{
    // powrot do panelu recepcjonistki
    emit powrotRec();
}

void listarezerwacji::on_pushButton_5_clicked()
{
    // zapisz zmiany daty
    emit listaZapisz();
}

void listarezerwacji::on_pushButton_clicked()
{
    // zamelduj
    emit listaZamelduj();
}

void listarezerwacji::on_pushButton_2_clicked()
{
    // wymelduj
    emit listaWymelduj();
}

void listarezerwacji::on_pushButton_3_clicked()
{
    // odwolaj rezerwacje
    emit listaAnuluj();
}

QString listarezerwacji::getDate(int i)
{
    if (i == 1)
    {
        return ui->odDaty->text();
    }
    if (i == 2)
    {
        return ui->doDaty->text();
    }
}

QString listarezerwacji::getReservationId()
{
    return ui->lineEdit->text();
}

