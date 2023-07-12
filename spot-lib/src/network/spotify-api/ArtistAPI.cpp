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
  QMap<QString, int> userFollowedArtistsMap;
  QList<ArtistPage*> userFollowedArtists;

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

  void requestArtistByID(const QString& id) {
    if (getArtistPageByID(id) != nullptr)
    {
      currentArtistID = id;
      emit parent->signalRequestArtistByIDFinished();
      return;
    }
  }
  void requestArtistCover(const QString& url, const QString& id)
  {
    QString fileName = "cache_imgs/" + url.split("/").last() + ".jpg";
    ArtistPage* artistPage = getArtistPageByID(id);
    if(artistPage == nullptr)
    {
      qDebug() << "ArtistAPI::requestArtistCover: artistPage is nullptr";
      return;
    }
    artistPage->imgFileName() = fileName;
    if (QFile::exists(fileName))
    {
      qDebug() << "ArtistAPI::requestArtistCover: file exists";
      emit artistPage->signalArtistPageRequestCoverFinished();
      return;
    }
    QNetworkRequest request(url);
    QNetworkReply* reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, id = id, this]() { onRequestArtistCover(reply, id); });
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
      QObject::connect(artistPage, &ArtistPage::signalArtistPageRequestCover, parent, [this](const QString& url, const QString& id) { requestArtistCover(url, id); });
      artistPages.append(artistPage);
      int index = artistPages.indexOf(artistPage); 
      artistPagesMap.insert(artistPage->id(), index);
    }
    emit parent->signalRequestUserFollowedArtistsFinished();
  }

  void onRequestArtistCover(QNetworkReply* reply, const QString& id)
  {
    if (!parent->log(reply, "RequestArtistCover"))
    {
      reply->deleteLater();
      return;
    }
    // Save the image
    ArtistPage* artistPage = getArtistPageByID(id);
    QByteArray data = reply->readAll();
    QFile file(artistPage->imgFileName());
    QDir dir;
    if (!dir.exists("cache_imgs")) {
      dir.mkpath("cache_imgs");
    }
    if (file.open(QIODevice::WriteOnly)) {
      file.write(data);
      file.close();
      qDebug() << "write a img file to " << artistPage->imgFileName();
      emit artistPage->signalArtistPageRequestCoverFinished();
    }
    else {
      qDebug() << "Failed to open file";
    }
    reply->deleteLater();
  }

  // HELPER FUNC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  ArtistPage* getArtistPageByID(const QString& id)
  {
    if (userFollowedArtistsMap.contains(id)) return userFollowedArtists[userFollowedArtistsMap[id]];
    if (artistPagesMap.contains(id)) return artistPages[artistPagesMap[id]];
    return nullptr;
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

void ArtistAPI::requestArtistByID(const QString& id)
{
  return impl->requestArtistByID(id);
}

ArtistPage* ArtistAPI::getCurrentArtistPage()
{
  return impl->getArtistPageByID(impl->currentArtistID);
}

QQmlListProperty<ArtistPage> ArtistAPI::artistPages()
{
  return QQmlListProperty<ArtistPage>(this, &impl->artistPages);
}

}}}