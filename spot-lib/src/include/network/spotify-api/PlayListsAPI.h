#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QQmlListProperty>
#include <QNetworkReply>
#include <QnetworkRequest>

#include "network/spotify-api/BaseAPI.h"
#include "data/playList.h"

using namespace libspot::data;

namespace libspot {
namespace network {
namespace API {

class PlayListsAPI : public BaseAPI
{
  Q_OBJECT
  Q_PROPERTY(QQmlListProperty<PlayList> playLists READ playLists CONSTANT)
public:
  explicit PlayListsAPI(QObject *parent, QString &access_token);
  ~PlayListsAPI() override;

  QQmlListProperty<PlayList> playLists();

  void getCurrentUserPlaylists();

  Q_INVOKABLE void getPlayListTracks(const QString &id);

signals: 
  void signalGetCurrentUserPlaylistsFinished();
  void signalGetPlayListTracksFinished();
  void signalMock();
private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}}
