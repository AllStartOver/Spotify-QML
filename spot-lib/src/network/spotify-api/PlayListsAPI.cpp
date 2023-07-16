#include "network/spotify-api/PlayListsAPI.h"

using namespace libspot::data;
namespace libspot {
namespace network {
namespace API {

class PlayListsAPI::Implementation
{
public:
  Implementation(PlayListsAPI* _parent, QString &_access_token)
    : parent(_parent),
      access_token(_access_token)
  {
  }

  PlayListsAPI *parent;
  QNetworkAccessManager* manager = NetworkManager::instance().getNetworkManager();
  QString& access_token;

  QMap<QString, int> playListsMap;
  QList<PlayList*> playLists;

  QString currentPlayListID;

  // MEMBER FUNCTIONS
  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  void getCurrentUserPlayLists()
  {
    QString endpoint = "me/playlists";
    QNetworkRequest request = parent->createBaseRequest(endpoint, access_token);
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, this]() { onGetCurrentUserPlayLists(reply); });
  }

  void getPlayListTracks(const QString &id)
  {
    if (!playLists[playListsMap[id]]->isEmpty())
    {
      currentPlayListID = id;
      qDebug() << "PlayListsAPI::getPlayListTracks: id = " << id;
      emit playLists[playListsMap[id]]->signalPlayListRequestTracksFinished();
      return;
    }
    QString endpoint = "playlists/" + id + "/tracks?limit=100";
    QNetworkRequest request = parent->createBaseRequest(endpoint, access_token);
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, id = id,  this]() { onGetPlayListTracks(reply, id); });
  }

  // SLOTS
  // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  void onGetCurrentUserPlayLists(QNetworkReply *reply)
  {
    if (!parent->log(reply, "GetCurrentUserPlayLists")) 
    {
      reply->deleteLater();
      return;
    }
    QByteArray data = reply->readAll();
    QJsonObject json = QJsonDocument::fromJson(data).object();
    playLists.clear();
    for (auto item : json["items"].toArray())
    {
      PlayList *playList = new PlayList(parent, item.toObject());
      playLists.append(playList);
      int index = playLists.indexOf(playList);
      playListsMap.insert(playList->id(), index);
    }
    reply->deleteLater();
    emit parent->signalGetCurrentUserPlaylistsFinished();
  }

  void onGetPlayListTracks(QNetworkReply *reply, const QString &id)
  {
    if (!parent->log(reply, "GetPlayListItems"))
    {
      reply->deleteLater();
      return;
    }
    QByteArray data = reply->readAll();
    QJsonObject json = QJsonDocument::fromJson(data).object();
    playLists[playListsMap[id]]->loadTracksFromJson(json);
    currentPlayListID = id;
    emit playLists[playListsMap[id]]->signalPlayListRequestTracksFinished();
    qDebug() << "PlayListsAPI::onGetPlayListTracks: id = " << id;
    reply->deleteLater();
  }
};
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PlayListsAPI::PlayListsAPI(QObject *parent, QString &access_token)
  : BaseAPI(parent)
{
  impl.reset(new Implementation(this, access_token));
}

PlayListsAPI::~PlayListsAPI()
{
}

QQmlListProperty<PlayList> PlayListsAPI::playLists()
{
  return QQmlListProperty<PlayList>(this, &impl->playLists);
}

void PlayListsAPI::getCurrentUserPlaylists()
{
  return impl->getCurrentUserPlayLists();
}

void PlayListsAPI::getPlayListTracks(const QString &id)
{
  return impl->getPlayListTracks(id);
}

PlayList* PlayListsAPI::getPlayListByID(const QString &id)
{
  return impl->playLists[impl->playListsMap[id]];
}

QString& PlayListsAPI::currentPlayListID()
{
  return impl->currentPlayListID;
}

}}}