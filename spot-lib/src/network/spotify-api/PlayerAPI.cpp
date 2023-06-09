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
    requestPlayerState();
  }

  void requestPlayerState()
  {
    QString endpoint = "";
    QNetworkRequest request = createBaseRequest(endpoint);
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, this]() { onGetPlayerState(reply); });
  }

  void pausePlayback()
  {
    QString endpoint = "/pause";
    QNetworkRequest request = createBaseRequest(endpoint);
    QNetworkReply *reply = manager->put(request, QByteArray());
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, this]() { onPausePlayback(reply); });
  }

  void resumePlayback()
  {
    QString endpoint = "/play";
    QNetworkRequest request = createBaseRequest(endpoint);
    QNetworkReply *reply = manager->put(request, QByteArray());
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, this]() { onResumePlayback(reply); });
  }

  void prevTrack()
  {
    QString endpoint = "/previous";
    QNetworkRequest request = createBaseRequest(endpoint);
    QNetworkReply *reply = manager->post(request, QByteArray());
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, this]() { onPrevTrack(reply); });
  }

  void nextTrack()
  {
    QString endpoint = "/next";
    QNetworkRequest request = createBaseRequest(endpoint);
    QNetworkReply *reply = manager->post(request, QByteArray());
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, this]() { onNextTrack(reply); });
  }

  void seekTrack(int positionMs)
  {
    QString endpoint = "/seek?position_ms=" + QString::number(positionMs);
    QNetworkRequest request = createBaseRequest(endpoint);

    QNetworkReply *reply = manager->put(request, QByteArray());
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, this]() { onSeekTrack(reply); });
  }

  // SLOTS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  void onGetPlayerState(QNetworkReply* reply)
  {
    if(reply->error() != QNetworkReply::NoError) 
    {
      qDebug() << "Error: " << reply->errorString();
      reply->deleteLater();
      return;
    }

    QByteArray data = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (doc.isNull() || !doc.isObject()) {
      qDebug() << "Failed to create JSON doc.";
      reply->deleteLater();
      return;
    }
    QJsonObject obj = doc.object();
    playerState.feed_json(obj);
    reply->deleteLater();
    emit parent->signalGetPlayerStateFinished();
  }

  void onPausePlayback(QNetworkReply* reply)
  {
    parent->log(reply, "Pause playback");
  }

  void onResumePlayback(QNetworkReply* reply)
  {
    parent->log(reply, "Resume playback");
  }

  void onPrevTrack(QNetworkReply* reply)
  {
    parent->log(reply, "Previous track");
  }

  void onNextTrack(QNetworkReply* reply)
  {
    parent->log(reply, "Next track");
  }

  void onSeekTrack(QNetworkReply* reply)
  {
    parent->log(reply, "Seek track");
  }

  // Helper functions
  QNetworkRequest createBaseRequest(QString& endpoint)
  {
    QNetworkRequest request(QUrl(baseURL + endpoint));
    request.setRawHeader("Authorization", "Bearer " + access_token.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    return request;
  }

  PlayerAPI* parent;
  QNetworkAccessManager* manager;

  QString baseURL = "https://api.spotify.com/v1/me/player";
  QString &access_token;
  libspot::data::PlayerState playerState;
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PlayerAPI::PlayerAPI(QString &access_token)
{
  impl.reset(new Implementation(this, access_token));
}

PlayerAPI::~PlayerAPI()
{
}

libspot::data::PlayerState& PlayerAPI::getPlayerState()
{
  return impl->playerState;
}

// Q_INVOKABLE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void PlayerAPI::pausePlayback()
{
  return impl->pausePlayback();
}

void PlayerAPI::resumePlayback()
{
  return impl->resumePlayback();
}

void PlayerAPI::prevTrack()
{
  return impl->prevTrack();
}

void PlayerAPI::nextTrack()
{
  return impl->nextTrack();
}

void PlayerAPI::seekTrack(int positionMs)
{
  return impl->seekTrack(positionMs);
}


QString& PlayerAPI::getCurrentDeviceId() const
{
  return impl->playerState.currentDeviceId();
}

QString& PlayerAPI::getCurrentDeviceName() const
{
  return impl->playerState.curentDeviceName();
}

// SLOTS
void PlayerAPI::onPausePlayback(QNetworkReply* reply)
{
  return impl->onPausePlayback(reply);
}

void PlayerAPI::onResumePlayback(QNetworkReply* reply)
{
  return impl->onResumePlayback(reply);
}

void PlayerAPI::onPrevTrack(QNetworkReply* reply)
{
  return impl->onPrevTrack(reply);
}

void PlayerAPI::onNextTrack(QNetworkReply* reply)
{
  return impl->onNextTrack(reply);
}

}}}