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
public:
  PlayerAPI(QString &access_token);
  ~PlayerAPI() override;

  void get() override;
  void post() override;
  void put() override;

  void pausePlayback();
  void resumePlayback();
signals:
  void signalPausePlayback(QNetworkReply* reply);
  void signalResumePlayback(QNetworkReply* reply);
public slots:
  void onPausePlayback(QNetworkReply* reply);
  void onResumePlayback(QNetworkReply* reply);
private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}}