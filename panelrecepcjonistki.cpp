#include "panelrecepcjonistki.h"
#include "ui_panelrecepcjonistki.h"

PanelRecepcjonistki::PanelRecepcjonistki(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PanelRecepcjonistki)
{
    ui->setupUi(this);
}

PanelRecepcjonistki::~PanelRecepcjonistki()
{
    delete ui;
}

void PanelRecepcjonistki::on_pushButton_clicked()
{
    // dodaj rezerwacje
    emit dodaj_rez();

}

void PanelRecepcjonistki::on_pushButton_2_clicked()
{
    // wyswietl rezerwacje
    emit wys_rez();
}

void PanelRecepcjonistki::on_pushButton_3_clicked()
{
    // dodaj usluge
}
void PanelRecepcjonistki::on_pushButton_4_clicked()
{
    emit wyloguj();
}


