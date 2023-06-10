#pragma once

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "network/spotify-api/BaseAPI.h"
#include "data/playerState.h"

namespace libspot {
namespace network {
namespace API {

class PlayerAPI : public BaseAPI
{
  Q_OBJECT
public:
  PlayerAPI(QString &access_token);
  ~PlayerAPI() override;

  Q_INVOKABLE void updatePlayerState(bool forceTrackUpdate);
  Q_INVOKABLE void pausePlayback();
  Q_INVOKABLE void resumePlayback();
  Q_INVOKABLE void prevTrack();
  Q_INVOKABLE void nextTrack();
  Q_INVOKABLE void seekTrack(int positionMs);
  Q_INVOKABLE void toggleShuffle(bool state);
  Q_INVOKABLE void setLoopMode(QString mode);

  libspot::data::PlayerState& getPlayerState();

  QString& getCurrentDeviceId() const;
  QString& getCurrentDeviceName() const;

signals:
  void signalPlayerStateUpdated();
  void signalGetPlayerStateFinished();

public slots:

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}}