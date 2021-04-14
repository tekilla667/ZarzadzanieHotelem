#ifndef PANELDODAWANIAREZERWACJI_H
#define PANELDODAWANIAREZERWACJI_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class PanelDodawaniaRezerwacji;
}

class PanelDodawaniaRezerwacji : public QWidget
{
    Q_OBJECT

public:
    explicit PanelDodawaniaRezerwacji(QWidget *parent = nullptr);
    ~PanelDodawaniaRezerwacji();
    QString getPokojeLine();
    QString getDowod();
    QString getWymeldowanie();
    QString getZameldowanie();
    QString getOsoby();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::PanelDodawaniaRezerwacji *ui;
signals:
    void rezerwujDodawanie();
    void powrotZDodawaniaDoRecepcjonistki();
};

#endif // PANELDODAWANIAREZERWACJI_H
