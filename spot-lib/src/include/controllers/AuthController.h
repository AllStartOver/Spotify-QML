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

inline const QString CLIENT_ID = QString("92134be6239042ee942a8c553f946b9b");
inline const QString CLIENT_SECRET = QString("1b87b0c02bf542b7993dfcd660ae1a31");
inline const QString REDIRECT_URL = QString("http://localhost:8888");

using namespace libspot::network;
using namespace libspot::setting;

namespace libspot {
namespace controllers {

class AuthController : public QObject
{
  Q_OBJECT
public:
  explicit AuthController(QObject *parent = 0, Account *account = 0);
  ~AuthController();

  void setupAuthorization();
  void openAuthPage() const;
  void refreshAccessToken();
  Account* getAccount() const;

  // status
  bool isAuthServerListening() const;

public slots:
  void onCodeReceived(QString code);
  void onTokenReceived(QString access_token, QString refresh_token);
  void onTokenRefreshed(QString access_token);

signals:
  void authFinished();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};
}}