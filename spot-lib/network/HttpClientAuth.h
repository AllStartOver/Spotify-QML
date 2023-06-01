#pragma once
#include <QObject>
#include <QScopedPointer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
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
  void processReply();

signals:
  void tokenReceived();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}