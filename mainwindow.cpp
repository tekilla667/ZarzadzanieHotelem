#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
 ui->setupUi(this);
    connect(&login, SIGNAL(loguj()),this,SLOT(zaloguj()));
    connect(&PanRcp, SIGNAL(wys_rez()), this, SLOT(wyswietl_rezerwacje()));
    connect(&PanRcp, SIGNAL(dodaj_rez()), this, SLOT(dodaj_rezerwacje()));
    connect(&listRez, SIGNAL(powrotRec()), this, SLOT(zListyDoRecep()));
    connect(&PanMag, SIGNAL(raport1()), this, SLOT(doRaportu1()));
    connect(&PanMag, SIGNAL(raport2()), this, SLOT(doRaportu2()));
    connect(&PanMag, SIGNAL(raport3()), this, SLOT(doRaportu3()));
    connect(&listRez, SIGNAL(listaZapisz()),this, SLOT (zapiszZmianyListaMain()));
    connect(&listRez, SIGNAL(listaZamelduj()), this, SLOT(listaZameldujMain()));
    connect(&listRez, SIGNAL(listaWymelduj()), this, SLOT(listaWymeldujMain()));
    connect(&listRez, SIGNAL(listaAnuluj()), this, SLOT(listaAnulujMain()));
    connect(&DodRez, SIGNAL(rezerwujDodawanie()), this, SLOT(rezerwujDodawanieMain()));
    connect(&DodRez, SIGNAL(powrotZDodawaniaDoRecepcjonistki()), this, SLOT(powrotZDodawaniaDoRecepcjonistki()));
    connect(&wyswietlraport, SIGNAL(powrot()),this, SLOT(powrot()));
    connect(&PanMag, SIGNAL(wyloguj()),this, SLOT(wyloguj()));
    connect(&PanRcp, SIGNAL(wyloguj()),this, SLOT(wyloguj()));
    connect(&PanMag, SIGNAL(raport1()),this,SLOT(raport1()));
    connect(&PanMag, SIGNAL(raport2()),this,SLOT(raport2()));
    connect(&PanMag, SIGNAL(raport3()),this,SLOT(raport3()));
    connect(&PanMag, SIGNAL(rezerwacje()),this,SLOT(wyswietlRezerwacje()));
    connect(&PanMag, SIGNAL(pracownicy()),this,SLOT(wyswietlPracownikow()));
    connect(&PanMag, SIGNAL(uslugi()),this,SLOT(wyswietlUslugi()));
    
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("D:/spanie1.db");
    if(!mydb.open())
       qDebug()<<"Nie otwarto";
    else
        qDebug()<<"Otwarto";
     ui->kontroler->addWidget(&login);
     ui->kontroler->addWidget(&PanMag);
     ui->kontroler->addWidget(&PanRcp); //nr 4
     ui->kontroler->addWidget(&DodRez); // nr 5
     ui->kontroler->addWidget(&listRez); //nr 6
     ui->kontroler->addWidget(&wyswietlraport); //nr 7
     ui->kontroler->setCurrentIndex(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QSqlDatabase MainWindow::bazaDanych()
{
    return mydb;
}

void MainWindow::zaloguj()
{
    if(!mydb.isOpen())
    {
            qDebug()<<"Failed to open";
    }
      QSqlQuery q_rec;
      q_rec.prepare("SELECT * FROM pracownicy where pesel = '"+login.PESEL+"' AND haslo = '"+login.haslo+"'");
       
           if(q_rec.exec())
           {
            QSqlQuery sekretarka, manager;
            bool Bmanager = false;
            bool Bsekretarka = false;

            sekretarka.prepare("SELECT recepcjonistki.IdRecepcjonistki, pracownicy.Pesel, pracownicy.haslo FROM recepcjonistki LEFT JOIN pracownicy ON recepcjonistki.IdPracownika = pracownicy.IdPracownika WHERE pracownicy.Pesel = '"+login.PESEL+"' AND pracownicy.haslo = '"+login.haslo+"';");
            manager.prepare("SELECT managerowie.IdManagera, pracownicy.Pesel, pracownicy.haslo FROM managerowie LEFT JOIN pracownicy ON managerowie.IdPracownika = pracownicy.IdPracownika WHERE pracownicy.Pesel = '"+login.PESEL+"' AND pracownicy.haslo = '"+login.haslo+"';");
            if(sekretarka.exec())
            while(sekretarka.next())
                  Bsekretarka=true;
            if(manager.exec())
            while(manager.next())
                  Bmanager=true;


            int count=0;
            while(q_rec.next())
            {
                count++;
            }
            if(count==1)
                login.wyswietlTekst("Zalogowano");
            else
                login.wyswietlTekst("bledne dane");

            if(Bmanager)
                ui->kontroler->setCurrentIndex(3);
            if(Bsekretarka)
                ui->kontroler->setCurrentIndex(4);

           }


}

void MainWindow::wyswietl_rezerwacje()
{
   wczesniejszyIndeks = ui->kontroler->currentIndex();

   QSqlQueryModel* modal = new QSqlQueryModel();

   QSqlQuery* query_resv = new QSqlQuery(mydb);
   query_resv->prepare("SELECT * FROM rezerwacje WHERE 1;");
   query_resv->exec();
   modal->setQuery(*query_resv);
   listRez.ustawModel(modal);
    ui->kontroler->setCurrentIndex(6);

}

void MainWindow::odswiezRezerwacje()
{
    wyswietlRaport("SELECT * FROM rezerwacje WHERE 1;");
    ui->kontroler->setCurrentIndex(7);
}

void MainWindow::dodaj_rezerwacje()
{
    ui->kontroler->setCurrentIndex(5);
}

void MainWindow::zListyDoRecep()
{
    ui->kontroler->setCurrentIndex(4);
}

void MainWindow::zapiszZmianyListaMain()
{
    QSqlQuery* query_zapisz = new QSqlQuery(mydb); // przekazanie db do klasy
    query_zapisz->prepare("UPDATE rezerwacje SET DataZameldowania  = '"+listRez.getDate(1)+"',  DataWymeldowania  = '" + listRez.getDate(2) + "' WHERE rezerwacje.NrRezerwacji = " + listRez.getReservationId() + ";");
    query_zapisz->exec();
}

void MainWindow::listaZameldujMain()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    QString year, month, day, date_now;
    year = QString::number(1900 + ltm->tm_year);
    month = QString::number(1 + ltm->tm_mon);
    if(month.size()==1)
        month = '0'+month;
    day = QString::number(ltm->tm_mday);
    if(day.size()==1)
    {
        day = '0'+day;
    }
    date_now = year + "-" + month + "-" + day;
    QSqlQuery* query_zameldowanie = new QSqlQuery(mydb); // przekazanie db do klasy
    QString zapytanieZamelduj = "UPDATE rezerwacje SET RzeczywistaDataZameldowania = '"+date_now+"' WHERE NrRezerwacji = " + listRez.getReservationId() + ";";
    qDebug()<<zapytanieZamelduj;
    query_zameldowanie->prepare(zapytanieZamelduj);
    query_zameldowanie->exec();
}

void MainWindow::listaWymeldujMain()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    QString year, month, day, date_now;
    year = QString::number(1900 + ltm->tm_year);
    month = QString::number(1 + ltm->tm_mon);
    if(month.size()==1)
        month = '0'+month;
    day = QString::number(ltm->tm_mday);
    if(day.size()==1)
    {
        day = '0'+day;
    }
    date_now = year + "-" + month + "-" + day;
    QSqlQuery* query_wymeldowanie = new QSqlQuery(mydb); // przekazanie db do klasy
    QString zapytanieWymelduj = "UPDATE rezerwacje SET RzeczywistaDataWymeldowania = '"+date_now+"' WHERE NrRezerwacji = " + listRez.getReservationId() + ";";
    qDebug()<<zapytanieWymelduj;
    query_wymeldowanie->prepare(zapytanieWymelduj);
    query_wymeldowanie->exec();
}

void MainWindow::listaAnulujMain()
{
    QSqlQuery* query_resv = new QSqlQuery(mydb); // przekazanie db do klasy
    query_resv->prepare("UPDATE rezerwacje SET czy_odwolana  = 'tak' WHERE rezerwacje.NrRezerwacji = " + listRez.getReservationId() + ";");
    query_resv->exec();
}

void MainWindow::doRaportu1()
{
    QString string;
    //raport 1 all
    if(PanMag.OdDatyRap1!=NULL && PanMag.odwolane == 0)
        string = "SELECT rezerwacje.NrRezerwacji, rezerwacje.DataZameldowania, rezerwacje.DataWymeldowania, klienci.Imie, klienci.Nazwisko, rezerwacje.Ilosc_osob, COUNT(pokoje_rezerwacje.NrPokoju) FROM rezerwacje LEFT JOIN klienci ON rezerwacje.NrDowoduKlienta = klienci.NrDowodu LEFT JOIN pokoje_rezerwacje ON pokoje_rezerwacje.NrRezerwacji = rezerwacje.NrRezerwacji WHERE rezerwacje.DataZameldowania > '" + PanMag.OdDatyRap1 + "' AND rezerwacje.DataZameldowania < '" + PanMag.DoDatyRap1 + "' GROUP BY rezerwacje.NrRezerwacji ORDER BY rezerwacje.DataZameldowania DESC" + ";";
    //raport 1 odwolane
    if(PanMag.OdDatyRap1!=NULL && PanMag.odwolane==1)
        string = "SELECT rezerwacje.NrRezerwacji, rezerwacje.DataZameldowania, rezerwacje.DataWymeldowania, klienci.Imie, klienci.Nazwisko, rezerwacje.Ilosc_osob, COUNT(pokoje_rezerwacje.NrPokoju) FROM rezerwacje LEFT JOIN klienci ON rezerwacje.NrDowoduKlienta = klienci.NrDowodu LEFT JOIN pokoje_rezerwacje ON pokoje_rezerwacje.NrRezerwacji = rezerwacje.NrRezerwacji WHERE rezerwacje.DataZameldowania > '" + PanMag.OdDatyRap1 + "' AND rezerwacje.DataZameldowania < '" + PanMag.DoDatyRap1 + "' AND rezerwacje.czy_odwolana='tak' GROUP BY rezerwacje.NrRezerwacji ORDER BY rezerwacje.DataZameldowania DESC" + ";";
    if (PanMag.OdDatyRap1 == NULL && PanMag.DoDatyRap1 == NULL && PanMag.odwolane ==0)
        string = "SELECT rezerwacje.NrRezerwacji, rezerwacje.DataZameldowania, rezerwacje.DataWymeldowania, klienci.Imie, klienci.Nazwisko, rezerwacje.Ilosc_osob, COUNT(pokoje_rezerwacje.NrPokoju) FROM rezerwacje LEFT JOIN klienci ON rezerwacje.NrDowoduKlienta = klienci.NrDowodu LEFT JOIN pokoje_rezerwacje ON pokoje_rezerwacje.NrRezerwacji = rezerwacje.NrRezerwacji GROUP BY rezerwacje.NrRezerwacji;";
    if (PanMag.OdDatyRap1 == NULL && PanMag.DoDatyRap1 == NULL && PanMag.odwolane ==1)
        string = "SELECT rezerwacje.NrRezerwacji, rezerwacje.DataZameldowania, rezerwacje.DataWymeldowania, klienci.Imie, klienci.Nazwisko, rezerwacje.Ilosc_osob, COUNT(pokoje_rezerwacje.NrPokoju) FROM rezerwacje LEFT JOIN klienci ON rezerwacje.NrDowoduKlienta = klienci.NrDowodu LEFT JOIN pokoje_rezerwacje ON pokoje_rezerwacje.NrRezerwacji = rezerwacje.NrRezerwacji WHERE rezerwacje.czy_odwolana='tak' GROUP BY rezerwacje.NrRezerwacji;";

    wyswietlRaport(string);
}

void MainWindow::doRaportu2()
{
    QString string;
    //raport 2 dla wszystkich
    if(PanMag.IdPracownika!= NULL && PanMag.PESEL!= NULL)
    string = "SELECT uslugi.Nazwa, pracownicy.Imie, pracownicy.Nazwisko, klienci.Nazwisko, uslugi.DataUslugi, uslugi.NrPokoju FROM uslugi LEFT JOIN klienci ON klienci.NrDowodu = uslugi.NrDowoduKlienta LEFT JOIN pracownicy ON uslugi.IdPracownika = pracownicy.IdPracownika WHERE pracownicy.IdPracownika=" + PanMag.IdPracownika + " AND klienci.NrDowodu='" + PanMag.PESEL + "' AND uslugi.DataUslugi > '" + PanMag.OdDatyRap2 + "' AND uslugi.DataUslugi < '" + PanMag.DoDatyRap2 + "' ORDER BY uslugi.DataUslugi DESC"+";";
    //raport 2 dla idpracownika
    if(PanMag.IdPracownika!= NULL && PanMag.PESEL == NULL )
    string = "SELECT uslugi.Nazwa, pracownicy.Imie, pracownicy.Nazwisko, klienci.Nazwisko, uslugi.DataUslugi, uslugi.NrPokoju FROM uslugi LEFT JOIN klienci ON klienci.NrDowodu = uslugi.NrDowoduKlienta LEFT JOIN pracownicy ON uslugi.IdPracownika = pracownicy.IdPracownika WHERE pracownicy.IdPracownika=" + PanMag.IdPracownika + " AND uslugi.DataUslugi > '" + PanMag.OdDatyRap2 + "' AND uslugi.DataUslugi < '" + PanMag.DoDatyRap2 + "' ORDER BY uslugi.DataUslugi DESC" + ";";
    //raport 2 dla niczego
    if(PanMag.IdPracownika == NULL && PanMag.PESEL == NULL )
    string = "SELECT uslugi.Nazwa, pracownicy.Imie, pracownicy.Nazwisko AS 'Nazwisko pracownika', klienci.Nazwisko AS 'Nazwisko klienta', uslugi.DataUslugi, uslugi.NrPokoju FROM uslugi LEFT JOIN klienci ON klienci.NrDowodu = uslugi.NrDowoduKlienta LEFT JOIN pracownicy ON uslugi.IdPracownika = pracownicy.IdPracownika WHERE uslugi.DataUslugi > '" + PanMag.OdDatyRap2 + "' AND uslugi.DataUslugi < '" + PanMag.DoDatyRap2 + "' ORDER BY uslugi.DataUslugi DESC" + ";";
    qDebug()<<string;
    // tylko nr dowodu
    if(PanMag.IdPracownika == NULL && PanMag.PESEL != NULL )
    string = "SELECT uslugi.Nazwa, pracownicy.Imie, pracownicy.Nazwisko, klienci.Nazwisko, uslugi.DataUslugi, uslugi.NrPokoju FROM uslugi LEFT JOIN klienci ON klienci.NrDowodu = uslugi.NrDowoduKlienta LEFT JOIN prac_rec ON uslugi.IdPracownika = pracownicy.IdPracownika  WHERE klienci.NrDowodu='" + PanMag.PESEL + "'  AND uslugi.DataUslugi > '" + PanMag.OdDatyRap2 + "' AND uslugi.DataUslugi < '" + PanMag.DoDatyRap2 + "' ORDER BY uslugi.DataUslugi DESC" + ";";
    wyswietlRaport(string);
}


void MainWindow::doRaportu3()
{
    QSqlQuery* query = new QSqlQuery(mydb);
    QString sqlQuery = "CREATE VIEW prac_rec AS SELECT pracownicy.*, recepcjonistki.IdRecepcjonistki FROM pracownicy RIGHT JOIN recepcjonistki ON recepcjonistki.IdPracownika = pracownicy.IdPracownika;";
    qDebug()<<sqlQuery;
    query->prepare(sqlQuery);
    query->exec();
    QString string;
    //raport 3 dla wszystkich
    if(PanMag.OdKwoty != NULL && PanMag.DoKwoty != NULL && PanMag.DoDatyRap3 != NULL && PanMag.OdDatyRap3 != NULL)
    string = "SELECT prac_rec.Imie, prac_rec.Nazwisko, rezerwacje.Kwota, rezerwacje.DataZameldowania, rezerwacje.DataWymeldowania, rezerwacje.Ilosc_osob, COUNT(pokoje_rezerwacje.NrPokoju) FROM rezerwacje LEFT JOIN prac_rec ON prac_rec.IdRecepcjonistki = rezerwacje.IdRecepcjonistki LEFT JOIN pokoje_rezerwacje ON pokoje_rezerwacje.NrRezerwacji = rezerwacje.NrRezerwacji WHERE rezerwacje.DataZameldowania > '" + PanMag.OdDatyRap3 + "' AND rezerwacje.DataZameldowania < '" + PanMag.DoDatyRap3 + "' AND rezerwacje.Kwota > " + PanMag.OdKwoty + " AND rezerwacje.Kwota < " + PanMag.DoKwoty + " GROUP BY rezerwacje.NrRezerwacji ORDER BY rezerwacje.DataZameldowania DESC" + ";";
    //raport 3 tylko dla dat
    if(PanMag.OdKwoty == NULL && PanMag.DoKwoty == NULL && PanMag.DoDatyRap3 != NULL && PanMag.OdDatyRap3 != NULL)
    string = "SELECT prac_rec.Imie, prac_rec.Nazwisko, rezerwacje.Kwota, rezerwacje.DataZameldowania, rezerwacje.DataWymeldowania, rezerwacje.Ilosc_osob, COUNT(pokoje_rezerwacje.NrPokoju) FROM rezerwacje LEFT JOIN prac_rec ON prac_rec.IdRecepcjonistki = rezerwacje.IdRecepcjonistki LEFT JOIN pokoje_rezerwacje ON pokoje_rezerwacje.NrRezerwacji = rezerwacje.NrRezerwacji WHERE rezerwacje.DataZameldowania > '" + PanMag.OdDatyRap3 + "' AND rezerwacje.DataZameldowania < '" + PanMag.DoDatyRap3 + "' GROUP BY rezerwacje.NrRezerwacji ORDER BY rezerwacje.DataZameldowania DESC" + ";";
    //raport 3 tylko dla kwot
    if(PanMag.OdKwoty != NULL && PanMag.DoKwoty != NULL && PanMag.DoDatyRap3 == NULL && PanMag.OdDatyRap3 == NULL)
    string = "SELECT prac_rec.Imie, prac_rec.Nazwisko, rezerwacje.Kwota, rezerwacje.DataZameldowania, rezerwacje.DataWymeldowania, rezerwacje.Ilosc_osob, COUNT(pokoje_rezerwacje.NrPokoju) FROM rezerwacje LEFT JOIN prac_rec ON prac_rec.IdRecepcjonistki = rezerwacje.IdRecepcjonistki LEFT JOIN pokoje_rezerwacje ON pokoje_rezerwacje.NrRezerwacji = rezerwacje.NrRezerwacji WHERE rezerwacje.Kwota > '" + PanMag.OdKwoty + "' AND rezerwacje.Kwota < '" + PanMag.DoKwoty + "' GROUP BY rezerwacje.NrRezerwacji ORDER BY rezerwacje.DataZameldowania DESC" + ";";
    //raport 3 bez danych
    if(PanMag.OdDatyRap3==NULL && PanMag.DoDatyRap3 == NULL && PanMag.OdKwoty == NULL && PanMag.DoKwoty == NULL)
        string = "SELECT prac_rec.Imie, prac_rec.Nazwisko, rezerwacje.Kwota, rezerwacje.DataZameldowania, rezerwacje.DataWymeldowania, rezerwacje.Ilosc_osob, COUNT(pokoje_rezerwacje.NrPokoju) FROM rezerwacje LEFT JOIN prac_rec ON prac_rec.IdRecepcjonistki = rezerwacje.IdRecepcjonistki LEFT JOIN pokoje_rezerwacje ON pokoje_rezerwacje.NrRezerwacji = rezerwacje.NrRezerwacji GROUP BY rezerwacje.NrRezerwacji ORDER BY rezerwacje.DataZameldowania DESC;";
    qDebug()<<string;
    wyswietlRaport(string);
}

void MainWindow::rezerwujDodawanieMain()
{
    std::vector<QString> pokoje = pokojeNumery(DodRez.getPokojeLine());
    QString pesel = login.PESEL;

    //SELECT PO ID recepcjonistki
    
    QSqlQueryModel *modal_rec = new QSqlQueryModel();
    QSqlQuery* query_rec = new QSqlQuery(mydb);
    QString zapytanko = "SELECT IdRecepcjonistki FROM recepcjonistki LEFT JOIN pracownicy ON pracownicy.IdPracownika = recepcjonistki.IdPracownika WHERE pracownicy.Pesel='" + pesel + "';";
    qDebug()<<"Pierwsze zapytanie"+zapytanko;
    query_rec->prepare(zapytanko);
    query_rec->exec();
    modal_rec->setQuery(*query_rec);
    int idRec = modal_rec->record(0).value(0).toInt();
    qDebug()<<idRec;
    //obliczenie kwoty
    int kwota = 0;
    for (int i = 0; i < (int)pokoje.size(); i++)
    {
        // GET STANDARD
        QSqlQueryModel* modal = new QSqlQueryModel();
        QSqlQuery* query_resv = new QSqlQuery(mydb); 
        query_resv->prepare("SELECT Standard FROM pokoje WHERE NrPokoju = "+pokoje[i]+";");
        query_resv->exec();
        modal->setQuery(*query_resv);
        int standard = modal->record(0).value(0).toString().toInt();
        // GET L. OSOB
        QSqlQueryModel* modal2 = new QSqlQueryModel();
        QSqlQuery* query_l = new QSqlQuery(mydb);
        query_l->prepare("SELECT Standard FROM pokoje WHERE NrPokoju = " + pokoje[i] + ";");
        query_l->exec();
        modal2->setQuery(*query_l);
        int liczba = modal2->record(0).value(0).toString().toInt();
        kwota = kwota + 50 * standard * liczba;
    }
    //INSERT
    QSqlQuery* query = new QSqlQuery(mydb);
    QString sqlQuery = "INSERT INTO rezerwacje(NrRezerwacji, IdRecepcjonistki, NrDowoduKlienta, DataZameldowania, DataWymeldowania, RzeczywistaDataZameldowania, RzeczywistaDataWymeldowania, Ilosc_osob, Kwota, czy_odwolana ) VALUES(NULL, "+QString::number(idRec)+", '"+DodRez.getDowod()+"', '"+DodRez.getZameldowanie()+"', '"+DodRez.getWymeldowanie()+"', '2000-01-01', '2000-01-01', "+DodRez.getOsoby()+", "+QString::number(kwota)+", 'nie');";
    qDebug()<<sqlQuery;
    query->prepare(sqlQuery);
    query->exec();

    //SELECT id rezerwacji
    QString sqlIdRez = "SELECT NrRezerwacji FROM rezerwacje ORDER BY NrRezerwacji DESC LIMIT 1";
    QSqlQueryModel* modal_id = new QSqlQueryModel();
    QSqlQuery* query_id = new QSqlQuery(mydb);
    query_id->prepare(sqlIdRez);
    query_id->exec();
    modal_id->setQuery(*query_id);
    QString nr = modal_id->record(0).value(0).toString();

    // dodawanie pokoje_rezerwacje
    for (int i = 0; i < (int)pokoje.size(); i++)
    {
        // dodanie pokoi do rezerwacji
        QSqlQuery* query_resv = new QSqlQuery(mydb); // 
        query_resv->prepare("INSERT INTO pokoje_rezerwacje (NrPolaczenia, NrRezerwacji, NrPokoju) VALUES (NULL, "+nr+", "+pokoje[i]+");");
        query_resv->exec();
    }
}

void MainWindow::powrotZDodawaniaDoRecepcjonistki()
{
    ui->kontroler->setCurrentIndex(4);
}

std::vector<QString> MainWindow::pokojeNumery(QString pok)
{
    std::vector<QString> wektor;
    QString pom;
    for(int i =0;i<pok.size();i++)
    {
        if(pok[i] == ',')
        {
            wektor.push_back(pom);
            pom = "";
        }
        else
        {
            pom.push_back(pok[i]);
        }
        if(i==pok.size()-1) wektor.push_back(pom);
    }
    return wektor;
}
void MainWindow::wyswietlRaport(QString zapytanie)
{
    wczesniejszyIndeks = ui->kontroler->currentIndex();
    QSqlQueryModel* modal = new QSqlQueryModel();
    QSqlQuery* query_resv = new QSqlQuery(mydb);
    query_resv->prepare(zapytanie);
    query_resv->exec();
    modal->setQuery(*query_resv);
    wyswietlraport.wyswietl(modal);
    ui->kontroler->setCurrentIndex(7);

}
void MainWindow::powrot()
{
    ui->kontroler->setCurrentIndex(wczesniejszyIndeks);
}
void MainWindow::wyloguj()
{
    login.wyczyscDane();
    ui->kontroler->setCurrentIndex(2);
}
void MainWindow::wyswietlPracownikow()
{
    wyswietlRaport("SELECT * FROM pracownicy;");
}

void MainWindow::wyswietlRezerwacje()
{
    wyswietlRaport("SELECT * FROM rezerwacje;");
}

void MainWindow::wyswietlUslugi()
{
    wyswietlRaport("SELECT * FROM uslugi;");
}
