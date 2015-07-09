#include "tester.h"
#include "ui_tester.h"

#include <QNetworkRequest>
#include <QUrl>

Tester::Tester(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tester)
{
    ui->setupUi(this);

    netManager = new QNetworkAccessManager(this);

    connect(netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
}

Tester::~Tester()
{
    delete ui;
}

void Tester::on_requestGet_clicked()
{
    QNetworkRequest request;
    request.setUrl(ui->webUrlPath->currentText());

    netManager->get(request);

    insertUrlPath();
}

void Tester::on_requestPost_clicked()
{
    QNetworkRequest request;
    request.setUrl(ui->webUrlPath->currentText());

    QByteArray data;

    for (int i = 0; i < ui->keyValuePairs->count(); i++) {
        data.append(i == 0 ? "" : "&").append(QString(QUrl::toPercentEncoding(ui->keyValuePairs->item(i)->text())).replace("%20", "+").replace("%3D", "="));
    }

    netManager->post(request, data);

    insertUrlPath();
}

void Tester::on_addPair_clicked()
{
    ui->keyValuePairs->addItem(new QListWidgetItem(ui->keyItem->text().append("=").append(ui->valueItem->text())));
    ui->keyItem->clear();
    ui->valueItem->clear();
}

void Tester::on_updatePair_clicked()
{
    ui->keyValuePairs->currentItem()->setText(ui->keyItem->text().append("=").append(ui->valueItem->text()));
    ui->keyItem->clear();
    ui->valueItem->clear();
}

void Tester::on_deletePair_clicked()
{
    ui->keyValuePairs->takeItem(ui->keyValuePairs->currentRow());
}

void Tester::requestFinished(QNetworkReply *reply)
{
    QList<QNetworkReply::RawHeaderPair> rawHeaders = reply->rawHeaderPairs();

    ui->responseRaw->clear();
    //

    QString attribute = QString("%1 %2")
            .arg(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString(),
                 reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString());

    ui->responseRaw->appendPlainText(attribute);

    for (int i = 0; i < rawHeaders.size(); ++i) {
        QString rawHeader;
        rawHeader.append(rawHeaders.at(i).first).append(": ").append(rawHeaders.at(i).second);

        ui->responseRaw->appendPlainText(rawHeader);
    }

    if (reply->isFinished()) {
        ui->responseRender->clear();
        ui->responseRender->append(reply->readAll());
    }
}

void Tester::insertUrlPath()
{
    QString currText = ui->webUrlPath->currentText();
    bool isContain = false;

    for (int i = 0; i < ui->webUrlPath->count(); ++i) {
        if (currText == ui->webUrlPath->itemText(i)) {
            isContain = true;
            break;
        }
    }

    if (!isContain) {
        ui->webUrlPath->addItem(currText);
    }
}
