#pragma once
#include <QObject>
#include <QScopedPointer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include "libSpotify_global.h"
#include "setting/account.h"

using namespace libspot::setting;
namespace libspot {
namespace network {

class HttpClientAuth : public QObject
{
  Q_OBJECT
public:
  HttpClientAuth(QObject *parent = 0, Account *account = 0);
  ~HttpClientAuth();

  void token_post(
    const QString code, 
    const QString redirect_url,
    const QString client_id,
    const QString client_secret
  );

  void refresh_post(
    const QString refresh_token,
    const QString client_id,
    const QString client_secret
  );

public slots:
  void onTokenReply(QNetworkReply *reply);
  void onRefreshReply(QNetworkReply *reply);

signals:
  void signalTokenReply(QNetworkReply *reply);
  void signalRefreshReply(QNetworkReply *reply);

  void tokenReceived(QString access_token, QString refresh_token);
  void tokenUpdated(QString access_token);
  void tokenExpired();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}