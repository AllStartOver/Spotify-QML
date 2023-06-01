#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QScopedPointer>
#include <QUrl>
#include <QString>
#include <QVector>
#include <QDebug>
#include "HttpClientAuth.h"
#include "libSpotify_global.h"

#ifdef WINDOWS
  #include <Windows.h>
  #include <ShellApi.h>
#endif

namespace libspot {
namespace network {

const QString AUTH_BASE_RUL = QString("https://accounts.spotify.com/authorize");

const QVector<QString> SCOPES = {
  "playlist-read-collaborative",
  "playlist-read-private",
  "playlist-modify-private",
  "playlist-modify-public",
  "user-follow-read",
  "user-follow-modify",
  "user-library-modify",
  "user-library-read",
  "user-modify-playback-state",
  "user-read-currently-playing",
  "user-read-playback-state",
  "user-read-private",
  "user-read-recently-played",
  "streaming",
  "user-read-email",
  "user-top-read"
};

const QString CLIENT_ID = QString("92f036ac89bc4899921c9a20b85bce4a");
const QString CLIENT_SECRET = QString("1d38b76e3d064049b065029e0c0e1207");


class LIBSPOTIFYSHARED_EXPORT AuthServer : public QTcpServer
{
  Q_OBJECT
public: 
  AuthServer(QObject *parent = 0);
  ~AuthServer();

  bool listen();
  void openAuthUrl() const;
  const QString& getCode() const;

signals:
  void codeReceived(const QString code, const QString redirect_url, const QString client_id, const QString client_secret);
  void tokenReceived();
  void testSignal();

public slots:
  void onNewConnection();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}

