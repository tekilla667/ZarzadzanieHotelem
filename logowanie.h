#ifndef LOGOWANIE_H
#define LOGOWANIE_H

#include <QWidget>
#include <QtSql>
namespace Ui {
class Logowanie;
}

class Logowanie : public QWidget
{
    Q_OBJECT

public:
    explicit Logowanie(QWidget *parent = nullptr);
    ~Logowanie();
    void wyswietlTekst(QString tekst);
    void wyczyscDane();
QString PESEL;
QString haslo;
private slots:
    void on_pushButton_clicked();
signals:
    void loguj();
private:
    Ui::Logowanie *ui;
QSqlDatabase mydbb;

};

#endif // LOGOWANIE_H
