#pragma once
#include <QObject>
#include <QMap>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QScopedPointer>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "network/NetworkManager.h"
namespace libspot {
namespace network {
namespace API {

class BaseAPI : public QObject
{
  Q_OBJECT
public:
  BaseAPI(){};
  virtual ~BaseAPI() {}

  bool log(QNetworkReply* reply, QString endpoint)
  {
    int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (reply->error() == QNetworkReply::NoError) {
      return true;
    }
    else {
      qDebug() << QString("%1 failed: %2 : %3").arg(endpoint).arg(status).arg(reply->errorString());
      return false;
    }
  }

  QNetworkRequest createBaseRequest(QString endpoint, QString& access_token)
  {
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.spotify.com/v1/" + endpoint));
    request.setRawHeader("Authorization", "Bearer " + access_token.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    return request;
  }
};

}}}