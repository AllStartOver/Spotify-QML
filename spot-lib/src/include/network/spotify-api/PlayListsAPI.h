#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QQmlListProperty>
#include <QNetworkReply>
#include <QnetworkRequest>
#include <QImage>

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
  Q_INVOKABLE void getCurrentUserPlaylists();
  void getPlayListTracks(const QString &id);
  Q_INVOKABLE PlayList* getPlayListByID(const QString &id);
  Q_INVOKABLE QString& currentPlayListID();
  Q_INVOKABLE void calculateAverageCoverColor(const QString &id);

public slots:

signals: 
  void signalGetCurrentUserPlaylistsFinished();
  void signalGetPlayListTracksFinished(QString id);
  void signalMock();
private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}}
