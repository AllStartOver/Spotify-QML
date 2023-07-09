#include "data/playerState.h"

namespace libspot {
namespace data {

class PlayerState::Implementation 
{
public:
  Implementation(PlayerState* _parent)
    : parent(_parent)
  {}

  void updateBasicStates(QJsonObject json)
  {
    qDebug() << "PlayerState::updateBasicStates() called";
    feed_json(json);
  }

  void updateFullStates(QJsonObject json)
  {
    qDebug() << "PlayerState::updateFullStates() called";
    if (json["item"].toObject()["name"].toString() == trackName)
    {
      emit parent->signalPlayerStateRemainsSame(true);
      return;
    }
    feed_json(json);
  }

  void feed_json(QJsonObject json)
  {

    // Track Info
    trackName = json["item"].toObject()["name"].toString();
    trackID = json["item"].toObject()["id"].toString();
    uri = json["context"].toObject()["uri"].toString();

    qDebug() << "PlayerState::feed_json() trackName: " << trackName << " trackID: " << trackID << " uri: " << uri;
    // Devices
    currentDeviceId = json["device"].toObject()["id"].toString();
    currentDeviceName = json["device"].toObject()["name"].toString();

    volumePercent = json["device"].toObject()["volume_percent"].toInt();

    // Progress and Duration
    progressMs = json["progress_ms"].toInt();
    durationMs = json["item"].toObject()["duration_ms"].toInt();

    // Basic States
    isPlaying = json["is_playing"].toBool();
    isShuffling = json["shuffle_state"].toBool();

    loopMode = json["repeat_state"].toString();

    // Update the Artists
    artists.clear();
    for(auto artist : json["item"].toObject()["artists"].toArray())
    {
      artists.append(new Artist(parent, artist.toObject()));
    }

    // Update the Image
    if (json["item"].toObject()["album"].toObject()["images"].toArray().size() == 0)
    {
      qDebug() << "PlayerState::feed_json() image not found";
      return;
    }
    else {
      qDebug() << "PlayerState::feed_json() image found";
      imageURL = json["item"].toObject()["album"].toObject()["images"].toArray()[0].toObject()["url"].toString();
    }
    emit parent->signalRequestImage(imageURL);

    qDebug() << "PlayerState::feed_json() finished";
    emit parent->signalPlayerStateUpdated();
    emit parent->signalContextChanged();
  }

  PlayerState* parent;

  QString currentDeviceId;
  QString currentDeviceName;

  int volumePercent;
  int progressMs;
  int durationMs;

  bool isPlaying;
  bool isShuffling;
  QString loopMode;

  QString trackName;
  QString trackID;
  QString uri;
  QString imageURL;

  QList<Artist*> artists;
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PlayerState::PlayerState(QObject* parent)
  : QObject(parent)
{
  impl.reset(new Implementation(this));
}

PlayerState::~PlayerState() {}

void PlayerState::updateBasicStates(QJsonObject json)
{
  impl->updateBasicStates(json);
}

void PlayerState::updateFullStates(QJsonObject json)
{
  impl->updateFullStates(json);
}


// Q_READ @@@@@@@@@@@@@@@@@@@@@@@@@@@@

QString& PlayerState::currentDeviceId() const
{
  return impl->currentDeviceId;
}

QString& PlayerState::curentDeviceName() const
{
  return impl->currentDeviceName;
}

int PlayerState::volumePercent() const
{
  return impl->volumePercent;
}

int PlayerState::progressMs() const
{
  return impl->progressMs;
}

int PlayerState::durationMs() const
{
  return impl->durationMs;
}

bool PlayerState::isPlaying() const
{
  return impl->isPlaying;
}

bool PlayerState::isShuffling() const
{
  return impl->isShuffling;
}

QString PlayerState::loopMode() const
{
  return impl->loopMode;
}

QString PlayerState::trackName() const
{
  return impl->trackName;
}

const QString& PlayerState::trackID() const
{
  return impl->trackID;
}

const QString& PlayerState::uri() const
{
  return impl->uri;
}


QQmlListProperty<Artist> PlayerState::artists()
{
  return QQmlListProperty<Artist>(this, &impl->artists);
}

// Q_WRITE @@@@@@@@@@@@@@@@@@@@@@@@@@@@

}}