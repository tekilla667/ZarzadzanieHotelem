#include "logowanie.h"
#include "ui_logowanie.h"
#include <QString>
Logowanie::Logowanie(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Logowanie)
{
    ui->setupUi(this);

}

Logowanie::~Logowanie()
{
    delete ui;
}

void Logowanie::on_pushButton_clicked()
{

    PESEL = ui->PESEL->text();
    haslo = ui->haslo->text();
    emit loguj();
}

void Logowanie::wyswietlTekst(QString tekst)
{
    ui->loginInfo->setText(tekst);
}
void Logowanie::wyczyscDane()
{
    ui->PESEL->setText("Podaj Pesel");
    ui->haslo->setText("Podaj haslo");
    
}
