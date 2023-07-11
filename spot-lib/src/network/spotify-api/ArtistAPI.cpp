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

  void requestArtistCover(const QString& url, const QString& id)
  {
    QString fileName = "cache_imgs/" + url.split("/").last() + ".jpg";
    artistPages[artistPagesMap[id]]->imgFileName() = fileName;
    if (QFile::exists(fileName))
    {
      qDebug() << "ArtistAPI::requestArtistCover: file exists";
      emit artistPages[artistPagesMap[id]]->signalArtistPageRequestCoverFinished();
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
    QByteArray data = reply->readAll();
    QFile file(artistPages[artistPagesMap[id]]->imgFileName());
    QDir dir;
    if (!dir.exists("cache_imgs")) {
      dir.mkpath("cache_imgs");
    }
    if (file.open(QIODevice::WriteOnly)) {
      file.write(data);
      file.close();
      qDebug() << "write a img file to " << artistPages[artistPagesMap[id]]->imgFileName();
      emit artistPages[artistPagesMap[id]]->signalArtistPageRequestCoverFinished();
    }
    else {
      qDebug() << "Failed to open file";
    }
    reply->deleteLater();
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