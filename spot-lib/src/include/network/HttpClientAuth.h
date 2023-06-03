#pragma once
#include <QObject>
#include <QScopedPointer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include "libSpotify_global.h"

namespace libspot {
namespace network {

class LIBSPOTIFYSHARED_EXPORT HttpClientAuth : public QObject
{
  Q_OBJECT
public:
  HttpClientAuth(QObject *parent = 0);
  ~HttpClientAuth();
  void post(
    const QString code, 
    const QString redirect_url,
    const QString client_id,
    const QString client_secret
  );

public slots:
  void processReply(QNetworkReply *reply);

signals:
  void tokenReceived(QString access_token, QString refresh_token);
  void tokenExpired();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}