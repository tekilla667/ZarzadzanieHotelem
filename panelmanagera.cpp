#include "panelmanagera.h"
#include "ui_panelmanagera.h"

panelmanagera::panelmanagera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::panelmanagera)
{
    ui->setupUi(this);
}

panelmanagera::~panelmanagera()
{
    delete ui;
}

void panelmanagera::on_pushButton_4_clicked()
{
    OdDatyRap1 = ui->od->text();
    DoDatyRap1 = ui->do_2->text();
    odwolane = ui->checkBox->checkState();
    emit raport1();
}

void panelmanagera::on_pushButton_5_clicked()
{
    OdDatyRap2 = ui->od2->text();
    DoDatyRap2 = ui->do2->text();
    PESEL = ui->pesel->text();
    IdPracownika = ui->idp->text();
    emit raport2();
}

void panelmanagera::on_pushButton_6_clicked()
{
    OdDatyRap3 = ui->od3->text();
    DoDatyRap3 = ui->do3->text();
    OdKwoty = ui->odkwoty->text();
    DoKwoty = ui->dokwoty->text();
    emit raport3();
}
void panelmanagera::on_pushButton_clicked()
{
    //rezerwacje
    emit rezerwacje();
}

void panelmanagera::on_pushButton_3_clicked()
{
    //pracownicy
    emit pracownicy();
}

void panelmanagera::on_pushButton_2_clicked()
{
    //uslugi
    emit uslugi();
}

void panelmanagera::on_pushButton_7_clicked()
{
    emit wyloguj();
}
