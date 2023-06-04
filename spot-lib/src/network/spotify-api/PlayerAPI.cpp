#include "network/spotify-api/PlayerAPI.h"

namespace libspot {
namespace network {
namespace API {

class PlayerAPI::Implementation
{
public:
  Implementation(PlayerAPI* _parent, QString &_access_token)
    : parent(_parent), 
      access_token(_access_token)
  {
    manager = new QNetworkAccessManager(parent);
  }

  void pausePlayback()
  {
    QNetworkRequest request(QUrl(baseURL + "/pause"));
    request.setRawHeader("Authorization", "Bearer " + access_token.toUtf8());
    QNetworkReply* reply = manager->put(request, QByteArray());
    emit parent->signalPausePlayback(reply);
  }

  void resumePlayback()
  {
    QNetworkRequest request(QUrl(baseURL + "/play"));
    request.setRawHeader("Authorization", "Bearer " + access_token.toUtf8());
    QNetworkReply* reply = manager->put(request, QByteArray());
    emit parent->signalResumePlayback(reply);
  }
  // SLOTS
  void onPausePlayback(QNetworkReply* reply)
  {
    if (reply->error() == QNetworkReply::NoError) {
      qDebug() << "Pause playback successful";
    }
    else {
      qDebug() << "Pause playback failed";
    }
    reply->deleteLater();
  }
  PlayerAPI* parent;
  QNetworkAccessManager* manager;

  QString baseURL = "https://api.spotify.com/v1/me/player";
  QString access_token;
};

PlayerAPI::PlayerAPI(QString &access_token)
{
  impl.reset(new Implementation(this, access_token));
}

PlayerAPI::~PlayerAPI()
{
}

void PlayerAPI::get()
{
}

void PlayerAPI::post()
{
}

void PlayerAPI::put()
{
}

void PlayerAPI::pausePlayback()
{
  return impl->pausePlayback();
}
// SLOTS
void PlayerAPI::onPausePlayback(QNetworkReply* reply)
{
  return impl->onPausePlayback(reply);
}

}}}