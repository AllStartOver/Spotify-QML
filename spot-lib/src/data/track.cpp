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
    for (auto artist : json["artists"].toArray()) {
      artists.append(new Artist(parent, artist.toObject()));
    }
    duration_ms = json["duration_ms"].toInt();
    QJsonArray img_urls = json["album"].toObject()["images"].toArray();
    img_url = img_urls[img_urls.size() - 1].toObject()["url"].toString();
    QObject::connect(parent, &Track::signalTrackRequestCover, [=](const QString& url) {
      getTrackCover(url);
    });
  }
  QNetworkAccessManager *manager = NetworkManager::instance().getNetworkManager();
  Track *parent;
  QString id;
  QString name;
  QString album;
  QString img_url;
  QString imgFileName;
  QString& context_uri;
  int duration_ms;
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
    }
    emit parent->signalTrackRequestCoverFinished();
  }
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

Track::Track(QObject *parent, QJsonObject json, QString& context_uri)
  : QObject(parent)
{
  impl.reset(new Implementation(this, json, context_uri));
}

Track::~Track() {}

QString Track::id() const { return impl->id; }
QString Track::name() const { return impl->name; }
QString Track::album() const { return impl->album; }
const QString& Track::img_url() const { return impl->img_url; }
const QString& Track::imgFileName() const { return impl->imgFileName; }
const QString& Track::context_uri() const { return impl->context_uri; }
int Track::duration_ms() const { return impl->duration_ms; }

QQmlListProperty<Artist> Track::artists()
{
  return QQmlListProperty<Artist>(this, &impl->artists);
}

}}