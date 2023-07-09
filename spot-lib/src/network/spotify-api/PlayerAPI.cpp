#include "network/spotify-api/PlayerAPI.h"

namespace libspot {
namespace network {
namespace API {

using namespace libspot::data;
class PlayerAPI::Implementation
{
public:
  Implementation(PlayerAPI* _parent, QString &_access_token)
    : parent(_parent), 
      access_token(_access_token)
  {
    manager = new QNetworkAccessManager(parent);
    QObject::connect(&playerState, &PlayerState::signalPlayerStateRemainsSame, parent, &PlayerAPI::updatePlayerState);
    QObject::connect(&playerState, &PlayerState::signalRequestImage, parent, [this](QString url) { requestImage(url); });
    requestPlayerState(true);
  }

  PlayerAPI* parent;
  QNetworkAccessManager* manager;

  QString baseURL = "https://api.spotify.com/v1/me/player";
  QString &access_token;
  libspot::data::PlayerState playerState;

  void requestPlayerState(bool forceTrackUpdate)
  {
    QString endpoint = "";
    QNetworkRequest request = createBaseRequest(endpoint);
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, forceTrackUpdate = forceTrackUpdate, this]() { onGetPlayerState(reply, forceTrackUpdate); });
  }

  void requestImage(QString url)
  {
    QString fileName = "cache_imgs/" + url.split("/").last() + ".jpg";
    if (QFile::exists(fileName))
    {
      qDebug() << "PlayerAPI::requestImage: file exists";
      emit playerState.signalRequestImageFinished(fileName);
      return;
    }
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, fileName = fileName, this]() { onRequestImage(reply, fileName); });
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

  void startPlayback(QString context_uri, int offset)
  {
    QString endpoint = "/play";
    QNetworkRequest request = createBaseRequest(endpoint);
    QJsonObject json;
    json["context_uri"] = context_uri;
    QJsonObject offsetJson;
    offsetJson["position"] = offset;
    json["offset"] = offsetJson;
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();
    QNetworkReply *reply = manager->put(request, data);
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, this]() { onStartPlayback(reply); });
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

  void toggleShuffle(bool state)
  {
    QString endpoint = "/shuffle?state=" + QString(state ? "true" : "false");
    QNetworkRequest request = createBaseRequest(endpoint);

    QNetworkReply *reply = manager->put(request, QByteArray());
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, this]() { onToggleShuffle(reply); });
  }

  void setLoopMode(QString mode)
  {
    QString endpoint = "/repeat?state=" + mode;
    QNetworkRequest request = createBaseRequest(endpoint);

    QNetworkReply *reply = manager->put(request, QByteArray());
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, this]() { onSetLoopMode(reply); });
  }

  // SLOTS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  void onGetPlayerState(QNetworkReply* reply, bool forceTrackUpdate)
  {
    int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "Status: " << status;
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
    forceTrackUpdate ? playerState.updateFullStates(obj) : playerState.updateBasicStates(obj);
    reply->deleteLater();
    emit parent->signalGetPlayerStateFinished();
  }

  void onRequestImage(QNetworkReply* reply, QString fileName)
  {
    if (!parent->log(reply, "Request image")) {
      reply->deleteLater();
      return;
    }
    // Save the image
    QByteArray data = reply->readAll();
    QFile file(fileName);
    QDir dir;
    if (!dir.exists("cache_imgs")) {
      dir.mkpath("cache_imgs");
    }
    if (file.open(QIODevice::WriteOnly)) {
      file.write(data);
      file.close();
    }
    else {
      qDebug() << "Failed to open file";
    }

    emit playerState.signalRequestImageFinished(fileName);
    reply->deleteLater();
  }

  void onPausePlayback(QNetworkReply* reply)
  {
    parent->log(reply, "Pause playback");
  }

  void onResumePlayback(QNetworkReply* reply)
  {
    parent->log(reply, "Resume playback");
  }

  void onStartPlayback(QNetworkReply* reply)
  {
    parent->log(reply, "Start playback");
    requestPlayerState(true);
  }

  void onPrevTrack(QNetworkReply* reply)
  {
    parent->log(reply, "Previous track");
    requestPlayerState(true);
  }

  void onNextTrack(QNetworkReply* reply)
  {
    parent->log(reply, "Next track");
    requestPlayerState(true);
  }

  void onSeekTrack(QNetworkReply* reply)
  {
    parent->log(reply, "Seek track");
  }

  void onToggleShuffle(QNetworkReply* reply)
  {
    parent->log(reply, "Toggle shuffle");
    requestPlayerState(false);
  }

  void onSetLoopMode(QNetworkReply* reply)
  {
    parent->log(reply, "Set loop mode");
    requestPlayerState(false);
  }

  // Helper functions
  QNetworkRequest createBaseRequest(QString& endpoint)
  {
    QNetworkRequest request(QUrl(baseURL + endpoint));
    request.setRawHeader("Authorization", "Bearer " + access_token.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    return request;
  }
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PlayerAPI::PlayerAPI(QObject *parent, QString &access_token)
  : BaseAPI(parent)
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

void PlayerAPI::updatePlayerState(bool forceTrackUpdate)
{
  return impl->requestPlayerState(forceTrackUpdate);
}

void PlayerAPI::pausePlayback()
{
  return impl->pausePlayback();
}

void PlayerAPI::resumePlayback()
{
  return impl->resumePlayback();
}

void PlayerAPI::startPlayback(QString context_uri, int offset)
{
  return impl->startPlayback(context_uri, offset);
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

void PlayerAPI::toggleShuffle(bool state)
{
  return impl->toggleShuffle(state);
}

void PlayerAPI::setLoopMode(QString mode)
{
  return impl->setLoopMode(mode);
}

// GETTERS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


QString& PlayerAPI::getCurrentDeviceId() const
{
  return impl->playerState.currentDeviceId();
}

QString& PlayerAPI::getCurrentDeviceName() const
{
  return impl->playerState.curentDeviceName();
}


}}}