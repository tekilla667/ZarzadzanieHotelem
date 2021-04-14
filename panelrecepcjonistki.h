#ifndef PANELRECEPCJONISTKI_H
#define PANELRECEPCJONISTKI_H

#include <QWidget>

namespace Ui {
class PanelRecepcjonistki;
}

class PanelRecepcjonistki : public QWidget
{
    Q_OBJECT

public:
    explicit PanelRecepcjonistki(QWidget *parent = nullptr);
    ~PanelRecepcjonistki();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::PanelRecepcjonistki *ui;
signals:
    void dodaj_rez();
    void wys_rez();
    void wyloguj();
};

#endif // PANELRECEPCJONISTKI_H
