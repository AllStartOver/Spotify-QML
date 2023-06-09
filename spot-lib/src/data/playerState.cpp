#include "data/playerState.h"

namespace libspot {
namespace data {

class PlayerState::Implementation 
{
public:
  Implementation(PlayerState* _parent)
    : parent(_parent)
  {}

  void feed_json(QJsonObject json)
  {
    currentDeviceId = json["device"].toObject()["id"].toString();
    currentDeviceName = json["device"].toObject()["name"].toString();

    volumePercent = json["device"].toObject()["volume_percent"].toInt();

    progressMs = json["progress_ms"].toInt();
    durationMs = json["item"].toObject()["duration_ms"].toInt();
    emit parent->durationMsChanged(durationMs);
    emit parent->progressMsChanged(progressMs);

    isPlaying = json["is_playing"].toBool();
    isShuffling = json["shuffle_state"].toBool();

    qDebug() << "PlayerState::feed_json() finished";

  }

  PlayerState* parent;

  QString currentDeviceId;
  QString currentDeviceName;

  int volumePercent;
  int progressMs;
  int durationMs;

  bool isPlaying;
  bool isShuffling;
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PlayerState::PlayerState()
  : QObject(nullptr)
{
  impl.reset(new Implementation(this));
}

PlayerState::~PlayerState() {}

void PlayerState::feed_json(QJsonObject json)
{
  impl->feed_json(json);
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

// Q_WRITE @@@@@@@@@@@@@@@@@@@@@@@@@@@@

void PlayerState::setProgressMs(int progressMs)
{
  impl->progressMs = progressMs;
  emit progressMsChanged(progressMs);
}

}}