#include "data/track.h"

using namespace libspot::network;

namespace libspot {
namespace data {

class Track::Implementation 
{
public:
  Implementation(Track* _parent, QJsonObject json, QString& _context_uri)
    : parent(_parent)
    , context_uri(_context_uri)
  {
    id = json["id"].toString();
    name = json["name"].toString();
    album = json["album"].toObject()["name"].toString();
    album_id = json["album"].toObject()["id"].toString();
    uri = json["uri"].toString();
    for (auto artist : json["artists"].toArray()) {
      artists.append(new Artist(parent, artist.toObject()));
    }
    duration_ms = json["duration_ms"].toInt();
    popularity = json["popularity"].toInt();

    // Image
    if(json["album"].toObject()["images"].toArray().size() == 0) {
      return;
    }
    else {
      QJsonArray images = json["album"].toObject()["images"].toArray();
      img_url = images[images.size()-1].toObject()["url"].toString();
    }

    QObject::connect(parent, &Track::signalTrackRequestCover, [=](const QString& url) {
      getTrackCover(url);
    });
  }

  Implementation(Track* _parent, QJsonObject json)
    : parent(_parent)
  {
    id = json["id"].toString();
    name = json["name"].toString();
    album = json["album"].toObject()["name"].toString();
    album_id = json["album"].toObject()["id"].toString();
    uri = json["uri"].toString();
    for (auto artist : json["artists"].toArray()) {
      artists.append(new Artist(parent, artist.toObject()));
    }
    duration_ms = json["duration_ms"].toInt();
    popularity = json["popularity"].toInt();
  }

  QNetworkAccessManager *manager = NetworkManager::instance().getNetworkManager();
  Track *parent;
  QString id;
  QString name;
  QString album;
  QString album_id;
  QString uri;
  QString img_url;
  QString imgFileName;
  QString context_uri;
  int duration_ms;
  int popularity;
  QList<Artist*> artists;

  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  void getTrackCover(const QString &url) 
  {
    QString fileName = "cache_imgs/" + url.split("/").last() + ".jpg";
    imgFileName = fileName;
    if(QFile::exists(fileName)) {
      emit parent->signalTrackRequestCoverFinished();
      return;
    }
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, parent,  [reply = reply, this]() {
      onGetTrackCover(reply);
    });
  }

  void onGetTrackCover(QNetworkReply *reply) 
  {
    if(reply->error() != QNetworkReply::NoError) {
      qDebug() << "Error: " << reply->errorString();
      return;
    }
    QFile file(imgFileName);
    if(file.open(QIODevice::WriteOnly)) {
      file.write(reply->readAll());
      file.close();
      emit parent->signalTrackRequestCoverFinished();
    }
  }
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

Track::Track(QObject *parent, QJsonObject json, QString& context_uri)
  : QObject(parent)
{
  impl.reset(new Implementation(this, json, context_uri));
}

Track::Track(QObject *parent, QJsonObject json)
  : QObject(parent)
{
  impl.reset(new Implementation(this, json));
}

Track::~Track() {}

QString Track::id() const { return impl->id; }
QString Track::name() const { return impl->name; }
QString Track::album() const { return impl->album; }
const QString& Track::album_id() const { return impl->album_id; }
const QString& Track::uri() const { return impl->uri; }
const QString& Track::img_url() const { return impl->img_url; }
const QString& Track::imgFileName() const { return impl->imgFileName; }
const QString& Track::context_uri() const { return impl->context_uri; }
int Track::duration_ms() const { return impl->duration_ms; }
int Track::popularity() const { return impl->popularity; }

QQmlListProperty<Artist> Track::artists()
{
  return QQmlListProperty<Artist>(this, &impl->artists);
}

}}