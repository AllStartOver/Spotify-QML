#include "network/spotify-api/AlbumAPI.h"

using namespace libspot::data;
using namespace libspot::network;

namespace libspot {
namespace network {
namespace API {

class AlbumAPI::Implementation
{
public:
  Implementation(AlbumAPI* _parent, QString &_access_token)
    : parent(_parent),
      access_token(_access_token)
  {
  }

  AlbumAPI* parent;
  QString& access_token;
  QNetworkAccessManager* manager = NetworkManager::instance().getNetworkManager();
  QMap<QString, int> albumsMap;
  QList<Album*> albums;
  QMap<QString, int> userSavedAlbumsMap;
  QList<Album*> userSavedAlbums;
  QString currentAlbumID;

  void requestUserSavedAlbums()
  {
    if (userSavedAlbums.size() > 0)
    {
      emit parent->signalRequestUserSavedAlbumsFinished();
      return;
    }
    QString endpoint = "me/albums";
    QNetworkRequest request = parent->createBaseRequest(endpoint, access_token);
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, this]() { onRequestUserSavedAlbums(reply); });
  }

  void requestAlbumByID(const QString &id)
  {
    if(userSavedAlbumsMap.keys().contains(id))
    {
      currentAlbumID = id;
      emit parent->signalRequestAlbumByIDFinished();
      return;
    }
    if(albumsMap.keys().contains(id))
    {
      currentAlbumID = id;
      emit parent->signalRequestAlbumByIDFinished();
      return;
    }
    QString endpoint = "albums/" + id;
    QNetworkRequest request = parent->createBaseRequest(endpoint, access_token);
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, id = id,  this]() { onRequestAlbumByID(reply, id); });
  }

  void requestAlbumCover(const QString& url, const QString& id)
  {
    QString fileName = "cache_imgs/" + url.split("/").last() + ".jpg";
    Album* album;
    if(userSavedAlbumsMap.keys().contains(id))
    {
      album = userSavedAlbums.at(userSavedAlbumsMap.value(id));
    }
    else
    {
      album = albums.at(albumsMap.value(id));
    }

    album->imgFileName() = fileName;
    if (QFile::exists(fileName))
    {
      emit album->signalAlbumRequestCoverFinished();
      return;
    }
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, id = id, this]() { onRequestAlbumCover(reply, id); });
  }

  // SLOTS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  void onRequestUserSavedAlbums(QNetworkReply *reply)
  {
    qDebug() << "AlbumAPI::onRequestUserSavedAlbums";
    if(!parent->log(reply, "RequestUserSavedAlbums"))
    {
      reply->deleteLater();
      return;
    }
    QByteArray data = reply->readAll();
    QJsonObject json = QJsonDocument::fromJson(data).object();
    for (auto item : json["items"].toArray())
    {
      Album* album = new Album(parent, item.toObject()["album"].toObject());
      QObject::connect(album, &Album::signalAlbumRequestCover, parent, [this](const QString& url, const QString& id) { requestAlbumCover(url, id); });
      userSavedAlbums.append(album);
      int index = userSavedAlbums.indexOf(album);
      userSavedAlbumsMap.insert(album->id(), index);
    }
    reply->deleteLater();
    emit parent->signalRequestUserSavedAlbumsFinished();
  }

  void onRequestAlbumByID(QNetworkReply *reply, const QString& id)
  {
    if(!parent->log(reply, "RequestAlbumByID"))
    {
      reply->deleteLater();
      return;
    }
    QByteArray data = reply->readAll();
    QJsonObject json = QJsonDocument::fromJson(data).object();
    Album* album = new Album(parent, json);
    QObject::connect(album, &Album::signalAlbumRequestCover, parent, [this](const QString& url, const QString& id) { requestAlbumCover(url, id); });
    albums.append(album);
    int index = albums.indexOf(album);
    albumsMap.insert(id, index);
    currentAlbumID = id;
    reply->deleteLater();
    emit parent->signalRequestAlbumByIDFinished();
  }

  void onRequestAlbumCover(QNetworkReply *reply, const QString &id)
  {
    if(!parent->log(reply, "RequestAlbumCover"))
    {
      reply->deleteLater();
      return;
    }
    Album* album;
    if (userSavedAlbumsMap.keys().contains(id))
    {
      album = userSavedAlbums[userSavedAlbumsMap[id]];
    }
    else
    {
      album = albums[albumsMap[id]];
    }
    QByteArray data = reply->readAll();
    QFile file(album->imgFileName());
    QDir dir;
    if (!dir.exists("cache_imgs")) {
      dir.mkpath("cache_imgs");
    }
    if (file.open(QIODevice::WriteOnly)) {
      file.write(data);
      file.close();
      qDebug() << "write a img file to " << album->imgFileName();
      emit album->signalAlbumRequestCoverFinished();
    }
    else {
      qDebug() << "Failed to open file";
    }
    reply->deleteLater();
  }

  // HELP_FUNCTION @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
};

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

AlbumAPI::AlbumAPI(QObject *parent, QString &access_token)
  : BaseAPI(parent)
{
  impl.reset(new Implementation(this, access_token));
}

AlbumAPI::~AlbumAPI()
{
}

void AlbumAPI::requestUserSavedAlbums()
{
  return impl->requestUserSavedAlbums();
}

void AlbumAPI::requestAlbumByID(const QString &id)
{
  return impl->requestAlbumByID(id);
}

Album* AlbumAPI::getAlbumByID(const QString &id)
{
  return impl->albums[impl->albumsMap[id]];
}

Album* AlbumAPI::getCurrentAlbum()
{
  Album* album;
  if (impl->userSavedAlbumsMap.keys().contains(impl->currentAlbumID))
  {
    album = impl->userSavedAlbums[impl->userSavedAlbumsMap[impl->currentAlbumID]];
    return album;
  }
  album = impl->albums[impl->albumsMap[impl->currentAlbumID]];
  return album;
}

QString& AlbumAPI::currentAlbumID() const
{
  return impl->currentAlbumID;
}

QQmlListProperty<Album> AlbumAPI::userSavedAlbums()
{
  return QQmlListProperty<Album>(this, &impl->userSavedAlbums);
}

}}}