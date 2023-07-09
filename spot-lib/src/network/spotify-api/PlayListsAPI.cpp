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
      emit parent->signalGetPlayListTracksFinished(id);
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
    playLists[playListsMap[id]]->imgFileName() = fileName;
    if (QFile::exists(fileName))
    {
      qDebug() << "PlayListsAPI::getPlayListCover: file exists";
      emit playLists[playListsMap[id]]->signalPlayListRequestCoverFinished();
      return;
    }
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, id = id, this]() { onGetPlayListCover(reply, id); });
  }

  void calculateAverageCoverColor(const QString &id)
  {
    QImage img(playLists[playListsMap[id]]->imgFileName());
    if (img.isNull())
    {
      qDebug() << "PlayListsAPI::calculateAverageCoverColor: image is null";
      return;
    }
    int r = 0, g = 0, b = 0;
    int count = 0;
    for (int x = 0; x < img.width(); x++)
    {
      for (int y = 0; y < img.height(); y++)
      {
        QColor color(img.pixel(x, y));
        r += color.red();
        g += color.green();
        b += color.blue();
        count++;
      }
    }
    r /= count;
    g /= count;
    b /= count;
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
      // Connect signals
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
    playLists[playListsMap[id]]->loadTracksFromJson(json);
    currentPlayListID = id;
    emit parent->signalGetPlayListTracksFinished(id);
    qDebug() << "PlayListsAPI::onGetPlayListTracks: id = " << id;
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
    QFile file(playLists[playListsMap[id]]->imgFileName());
    QDir dir;
    if (!dir.exists("cache_imgs")) {
      dir.mkpath("cache_imgs");
    }
    if (file.open(QIODevice::WriteOnly)) {
      file.write(data);
      file.close();
      qDebug() << "write a img file to " << playLists[playListsMap[id]]->imgFileName();
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

void PlayListsAPI::calculateAverageCoverColor(const QString& id)
{
  return impl->calculateAverageCoverColor(id);
}

}}}