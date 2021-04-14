#ifndef WYSWIETLRAPORT_H
#define WYSWIETLRAPORT_H

#include <QWidget>
#include <QString>
#include <QSqlQueryModel>
namespace Ui {
class WyswietlRaport;
}

class WyswietlRaport : public QWidget
{
    Q_OBJECT

public:
    explicit WyswietlRaport(QWidget *parent = nullptr);
    ~WyswietlRaport();
    void wyswietl(QSqlQueryModel * modal);
private slots:
    void on_pushButton_clicked();
signals:
    void powrot();
private:
    Ui::WyswietlRaport *ui;
};

#endif // WYSWIETLRAPORT_H
