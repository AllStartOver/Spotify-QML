#pragma once

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "network/spotify-api/BaseAPI.h"

namespace libspot {
namespace network {
namespace API {

class PlayerAPI : public BaseAPI
{
  Q_OBJECT
public:
  PlayerAPI(QString &access_token);
  ~PlayerAPI() override;

  Q_INVOKABLE void pausePlayback();
  Q_INVOKABLE void resumePlayback();
  Q_INVOKABLE void prevTrack();
  Q_INVOKABLE void nextTrack();
signals:
  void signalPausePlayback(QNetworkReply* reply);
  void signalResumePlayback(QNetworkReply* reply);
public slots:
  void onPausePlayback(QNetworkReply* reply);
  void onResumePlayback(QNetworkReply* reply);
  void onPrevTrack(QNetworkReply* reply);
  void onNextTrack(QNetworkReply* reply);
private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}}