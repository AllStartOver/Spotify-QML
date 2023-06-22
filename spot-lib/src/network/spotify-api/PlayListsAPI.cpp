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
    manager = new QNetworkAccessManager(parent);
  }

  PlayListsAPI* parent;
  QNetworkAccessManager* manager;
  QString& access_token;

  QMap<QString, PlayList*> playLists;

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
    qDebug() << "find " << json["items"].toArray().size() << " playlists";
    for (auto item : json["items"].toArray())
    {
      PlayList *playList = new PlayList(parent, item.toObject());
      playLists.insert(playList->id(), playList);
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
    playLists[id]->loadTracksFromJson(json);
    reply->deleteLater();
  }
};
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PlayListsAPI::PlayListsAPI(QObject *parent, QString &access_token)
{
  impl.reset(new Implementation(this, access_token));
}

PlayListsAPI::~PlayListsAPI()
{
}

QQmlListProperty<PlayList> PlayListsAPI::playLists()
{
  QList<PlayList*> *values = new QList<PlayList*>(impl->playLists.values());
  return QQmlListProperty<PlayList>(this, values);
}

void PlayListsAPI::getCurrentUserPlaylists()
{
  return impl->getCurrentUserPlayLists();
}

void PlayListsAPI::getPlayListTracks(const QString &id)
{
  return impl->getPlayListTracks(id);
}


}}}