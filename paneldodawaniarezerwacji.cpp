#include "paneldodawaniarezerwacji.h"
#include "ui_paneldodawaniarezerwacji.h"

PanelDodawaniaRezerwacji::PanelDodawaniaRezerwacji(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PanelDodawaniaRezerwacji)
{
    ui->setupUi(this);
}

PanelDodawaniaRezerwacji::~PanelDodawaniaRezerwacji()
{
    delete ui;
}

void PanelDodawaniaRezerwacji::on_pushButton_clicked()
{
    // rezerwuj
    qDebug() <<"emit dodawanie";
    emit rezerwujDodawanie();
}

void PanelDodawaniaRezerwacji::on_pushButton_2_clicked()
{
    // powrot do panelu recepcjonistki
    emit powrotZDodawaniaDoRecepcjonistki();
}

QString PanelDodawaniaRezerwacji::getPokojeLine()
{
    return ui->lineEdit_2->text();
}

QString PanelDodawaniaRezerwacji::getDowod()
{
    return ui->lineEdit->text();
}

QString PanelDodawaniaRezerwacji::getZameldowanie()
{
    return ui->zameldowanko->text();
}

QString PanelDodawaniaRezerwacji::getWymeldowanie()
{
    return ui->wymeldowanko->text();
}

QString PanelDodawaniaRezerwacji::getOsoby()
{
    return ui->lineEdit_3->text();
}
