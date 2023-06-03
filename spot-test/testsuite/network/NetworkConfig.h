#pragma once
#include <QString>
#include <QUrl>
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

inline const QUrl URL_TOKEN = QUrl("https://accounts.spotify.com/api/token");
inline const QString CODE_EXPIRED = QString("AQDf61CDdsXfby8OSaY7nZYVvajKGwapTQPJaCM4wAqmpz_3GRC36nwXS2lhIaSjztb5Q82rxJ8LGdTChbvRb4kBedYm1LtA6L-wd-Kcagr882ddgpgtZuxbPYAmfYP-xRriprxtJ3odISt5_HR7UHPNeNM6uAJ1C1WN3IE8Djrtrfot-YACbYEmhRylvRpqPgNFda6y0cnu95Zum0chhgvR-ol8CSZjjmHk6Z-mA6vxB4pGF9IXntpD-q9U-s0QavgSpI8MyhPk5pobJfmHa0pts9yn3DxnnYckvE1F44LfnycDB-CJKQlWC80kQ9PYmJLMFBmt31wOum3mypuNYRkMXo0F1lJiVfEfSbCUimTBHeKR_qJb1CGxK_8NjZe0TR0RAthnn_BN9ocxVSggZBE8tXK1MYHiHgADh-Wn1wTKyZfd4YQBwBnzVXI1GiGTsHqKPfRKyDJNIK7NKKgmxuwlmbyIXhZvDtMrmSTaOBzBy5mhCSGcMvluufbD3pdb-kcV9bnrkplS7tbzom9FSk6GCsVUEoDcHx51K89g8Q4UXiditoN8lUT5c1hTJuYuL0SVJGB46gK5DTp6XhEiFaXwVJZVrLOIpRq3-57AN5CoP4DLTZ6e1A");
QString CODE_TEST;
}}}