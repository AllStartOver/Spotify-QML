#pragma once
#include <QObject>
#include <QDebug>
#include <QScopedPointer>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
namespace libspot {
namespace network {
namespace API {

class BaseAPI : public QObject
{
  Q_OBJECT
public:
  BaseAPI(){};
  virtual ~BaseAPI() {}

  void log(QNetworkReply* reply, QString endpoint)
  {
    int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (reply->error() == QNetworkReply::NoError) {
      qDebug() << QString("%1 successful: %2").arg(endpoint).arg(reply->readAll());
    }
    else {
      qDebug() << QString("%1 failed: %2 : %3").arg(endpoint).arg(status).arg(reply->errorString());
    }
    reply->deleteLater();
  }
};

}}}