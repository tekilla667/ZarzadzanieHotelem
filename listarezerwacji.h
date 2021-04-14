#ifndef LISTAREZERWACJI_H
#define LISTAREZERWACJI_H

#include <QWidget>
#include <QDebug>
#include <logowanie.h>

namespace Ui {
class listarezerwacji;
}

class listarezerwacji : public QWidget
{
    Q_OBJECT

public:
    explicit listarezerwacji(QWidget *parent = nullptr);
    ~listarezerwacji();
    QString getDate(int i);
    void ustawModel(QSqlQueryModel* modal);
    QString getReservationId();
private:
    Ui::listarezerwacji *ui;

signals:
    void powrotRec();
    void listaZapisz();
    void listaZamelduj();
    void listaWymelduj();
    void listaAnuluj();

private slots:
    void on_pushButton_5_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_6_clicked();
};

#endif // LISTAREZERWACJI_H
