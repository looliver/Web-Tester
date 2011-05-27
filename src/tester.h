#ifndef TESTER_H
#define TESTER_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
    class Tester;
}

class Tester : public QWidget
{
    Q_OBJECT

private slots:
    void on_requestGet_clicked();
    void on_requestPost_clicked();
    void on_addPair_clicked();
    void on_updatePair_clicked();
    void on_deletePair_clicked();

    void requestFinished(QNetworkReply *reply);

public:
    explicit Tester(QWidget *parent = 0);
    ~Tester();

private:
    Ui::Tester *ui;

    QNetworkAccessManager *netManager;

    void insertUrlPath();
};

#endif // TESTER_H
