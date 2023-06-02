#pragma once
#include <QString>
#include <QVector>

namespace libspot {
namespace network {
namespace config {

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
}}}