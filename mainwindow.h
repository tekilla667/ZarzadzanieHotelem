#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <logowanie.h>
#include <panelmanagera.h>
#include <panelrecepcjonistki.h>
#include <paneldodawaniarezerwacji.h>
#include <listarezerwacji.h>
#include <panelmanagera.h>
#include <wyswietlraport.h>
#include <ctime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlDatabase bazaDanych();
    std::vector<QString> pokojeNumery(QString pok);

private slots:
    void zaloguj();
    void wyswietl_rezerwacje();
    void dodaj_rezerwacje();
    void zListyDoRecep();
    void zapiszZmianyListaMain();
    void listaZameldujMain();
    void listaWymeldujMain();
    void listaAnulujMain();
    void wyswietlRaport(QString zapytanie);
    void powrot();
    void rezerwujDodawanieMain();
    void powrotZDodawaniaDoRecepcjonistki();
    void wyloguj();
    void doRaportu1();
    void doRaportu2();
    void doRaportu3();
    void wyswietlPracownikow();
    void wyswietlRezerwacje();
    void wyswietlUslugi();
private:
    Ui::MainWindow *ui;
    Logowanie login;
    QSqlDatabase mydb;
    panelmanagera PanMag; // nr 3
    PanelRecepcjonistki PanRcp; // nr 4
    PanelDodawaniaRezerwacji DodRez; // nr 5
    listarezerwacji listRez; //nr 6
    WyswietlRaport wyswietlraport; //nr7
    int wczesniejszyIndeks;
    void odswiezRezerwacje();
};
#endif // MAINWINDOW_H
