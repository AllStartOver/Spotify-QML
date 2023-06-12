#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>
#include <QnetworkRequest>

#include "network/spotify-api/BaseAPI.h"

namespace libspot {
namespace network {
namespace API {

class PlayListsAPI : public BaseAPI
{
  Q_OBJECT
public:
  explicit PlayListsAPI(QObject *parent, QString &access_token);
  ~PlayListsAPI() override;

  void getCurrentUserPlaylists();
private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}}
