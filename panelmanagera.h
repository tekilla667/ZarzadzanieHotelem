#ifndef PANELMANAGERA_H
#define PANELMANAGERA_H

#include <QWidget>
#include <QDebug>
#include <QString>

namespace Ui {
class panelmanagera;
}

class panelmanagera : public QWidget
{
    Q_OBJECT

public:
    explicit panelmanagera(QWidget *parent = nullptr);
    ~panelmanagera();
    QString OdDatyRap1 = NULL;
    QString DoDatyRap1 = NULL;
    QString OdDatyRap2 = NULL;
    QString DoDatyRap2 = NULL;
    QString OdDatyRap3 = NULL;
    QString DoDatyRap3 = NULL;
    QString PESEL = NULL;
    QString IdPracownika = NULL;
    QString OdKwoty = NULL;
    QString DoKwoty = NULL;
    bool odwolane;

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::panelmanagera *ui;

signals:
    void raport1();
    void raport2();
    void raport3();
    void rezerwacje();
    void pracownicy();
    void uslugi();
    void wyloguj();
};


#endif // PANELMANAGERA_H
