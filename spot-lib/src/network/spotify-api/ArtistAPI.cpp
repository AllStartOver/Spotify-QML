#include "network/spotify-api/ArtistAPI.h"

namespace libspot {
namespace network {
namespace API {

class ArtistAPI::Implementation
{
public:
  Implementation(ArtistAPI* _parent, QString &_access_token)
    : parent(_parent),
      access_token(_access_token)
  {
  }

  ArtistAPI* parent;
  QString& access_token;
  QNetworkAccessManager* manager = NetworkManager::instance().getNetworkManager();

  QMap<QString, int> artistPagesMap;
  QList<ArtistPage*> artistPages;
  QString currentArtistID;

  // MEMBER FUNC @@@@@@@@@@@@@@@@@@@@@@@
  void requestUserFollowedArtists()
  {
    if (!artistPages.isEmpty())
    {
      emit parent->signalRequestUserFollowedArtistsFinished();
      return;
    }
    QString endpoint = "me/following?type=artist";
    QNetworkRequest request = parent->createBaseRequest(endpoint, access_token);
    QNetworkReply* reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, this]() { onRequestUserFollowedArtists(reply); });
  }

  // SLOTS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  void onRequestUserFollowedArtists(QNetworkReply *reply)
  {
    if(!parent->log(reply, "RequestUserFollowedArtists"))
    {
      reply->deleteLater();
      return;
    }
    QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
    for (auto artist : json["artists"].toObject()["items"].toArray())
    {
      ArtistPage* artistPage = new ArtistPage(parent, artist.toObject());
      artistPages.append(artistPage);
      int index = artistPages.indexOf(artistPage); 
      artistPagesMap.insert(artistPage->id(), index);
    }
    emit parent->signalRequestUserFollowedArtistsFinished();
  }
};

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

ArtistAPI::ArtistAPI(QObject *parent, QString &access_token)
  : BaseAPI(parent)
{
  impl.reset(new Implementation(this, access_token));
}

ArtistAPI::~ArtistAPI()
{
}

void ArtistAPI::requestUserFollowedArtists()
{
  return impl->requestUserFollowedArtists();
}

QQmlListProperty<ArtistPage> ArtistAPI::artistPages()
{
  return QQmlListProperty<ArtistPage>(this, &impl->artistPages);
}

}}}