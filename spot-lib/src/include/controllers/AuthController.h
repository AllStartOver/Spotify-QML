#pragma once

#include <QObject>
#include <QScopedPointer>
#include "network/AuthServer.h"
#include "network/HttpClientAuth.h"
#include "setting/account.h"

#include "libSpotify_global.h"

#ifdef WINDOWS
  #include <Windows.h>
  #include <ShellApi.h>
#endif

inline const QString AUTH_BASE_RUL = QString("https://accounts.spotify.com/authorize");

inline const QVector<QString> SCOPES = {
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

inline const QString CLIENT_ID = QString("92f036ac89bc4899921c9a20b85bce4a");
inline const QString CLIENT_SECRET = QString("1d38b76e3d064049b065029e0c0e1207");
inline const QString REDIRECT_URL = QString("http://localhost:8888");

using namespace libspot::network;

namespace libspot {
namespace controllers {

class LIBSPOTIFYSHARED_EXPORT AuthController : public QObject
{
  Q_OBJECT
public:
  AuthController(QObject *parent = 0);
  ~AuthController();

  void setupAuthorization();
  void openAuthPage() const;
  libspot::setting::Account* getAccount() const;

  // status
  bool isAuthServerListening() const;

public slots:
  void onCodeReceived(QString code);
  void onTokenReceived(QString access_token, QString refresh_token);

signals:
  void authFinished();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};
}}