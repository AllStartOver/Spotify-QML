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
  QMap<QString, Album*> albums;
  QString currentAlbumID;

  void requestAlbumByID(const QString &id)
  {
    if(albums.contains(id))
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

  void onRequestAlbumByID(QNetworkReply *reply, const QString& id)
  {
    if(!parent->log(reply, "RequestAlbumByID"))
    {
      reply->deleteLater();
      return;
    }
    QByteArray data = reply->readAll();
    QJsonObject json = QJsonDocument::fromJson(data).object();
    albums.insert(id, new Album(parent, json));
    currentAlbumID = id;
    reply->deleteLater();
    emit parent->signalRequestAlbumByIDFinished();
  }
};

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

AlbumAPI::AlbumAPI(QObject *parent, QString &access_token)
{
  impl.reset(new Implementation(this, access_token));
}

AlbumAPI::~AlbumAPI()
{
}

void AlbumAPI::requestAlbumByID(const QString &id)
{
  return impl->requestAlbumByID(id);
}

Album* AlbumAPI::getAlbumByID(const QString &id)
{
  return impl->albums[id];
}

Album* AlbumAPI::getCurrentAlbum()
{
  qDebug() << "getCurrentAlbum(): currentAlbumID: " << impl->currentAlbumID;
  return impl->albums[impl->currentAlbumID];
}

QString& AlbumAPI::currentAlbumID() const
{
  return impl->currentAlbumID;
}

}}}