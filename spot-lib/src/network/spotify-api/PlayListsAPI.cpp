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

  PlayListsAPI *parent;
  QNetworkAccessManager* manager;
  QString& access_token;

  QMap<QString, PlayList*> playLists;
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
    if (!playLists[id]->isEmpty())
    {
      emit parent->signalGetPlayListTracksFinished(id);
      qDebug() << "playlist already loaded";
      currentPlayListID = id;
      return;
    }
    QString endpoint = "playlists/" + id + "/tracks?limit=100";
    QNetworkRequest request = parent->createBaseRequest(endpoint, access_token);
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, id = id,  this]() { onGetPlayListTracks(reply, id); });
  }

  void getPlayListCover(const QString& url, const QString& id)
  {
    QString fileName = "cache_imgs/" + url.split("/").last() + ".jpg";
    playLists[id]->imgFileName() = fileName;
    if (QFile::exists(fileName))
    {
      qDebug() << "file exists";
      emit playLists[id]->signalPlayListRequestCoverFinished();
      return;
    }
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, id = id, this]() { onGetPlayListCover(reply, id); });
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
      playLists.insert(playList->id(), playList);
      QObject::connect(playList, &PlayList::signalPlayListRequestCover, parent, [this](const QString& url, const QString& id) { getPlayListCover(url, id); });
      QObject::connect(playList, &PlayList::signalPlayListRequestTracks, parent, [this](const QString& id) { getPlayListTracks(id); });
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
    emit parent->signalGetPlayListTracksFinished(id);
    currentPlayListID = id;
    reply->deleteLater();
  }
  void onGetPlayListCover(QNetworkReply *reply, const QString &id)
  {
    if (!parent->log(reply, "GetPlayListCover"))
    {
      reply->deleteLater();
      return;
    }
    // Save the image
    QByteArray data = reply->readAll();
    QFile file(playLists[id]->imgFileName());
    QDir dir;
    if (!dir.exists("cache_imgs")) {
      dir.mkpath("cache_imgs");
    }
    if (file.open(QIODevice::WriteOnly)) {
      file.write(data);
      file.close();
      qDebug() << "write a img file to " << playLists[id]->imgFileName();
    }
    else {
      qDebug() << "Failed to open file";
    }
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

PlayList* PlayListsAPI::getPlayListByID(const QString &id)
{
  return impl->playLists[id];
}

QString& PlayListsAPI::currentPlayListID()
{
  return impl->currentPlayListID;
}

}}}