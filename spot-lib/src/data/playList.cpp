#include "data/playList.h"

namespace libspot {
namespace data {

class PlayList::Implementation 
{
public:
  Implementation(PlayList *_parent, QJsonObject json)
    : parent(_parent)
  {
    id = json.contains("id") ? json["id"].toString() : "";
    name = json.contains("name") ? json["name"].toString() : "Liked Songs";
    QJsonArray img_urls = json["images"].toArray();
    if (img_urls.size() > 0) {
      img_url = img_urls[0].toObject()["url"].toString();
    }
    tracks_href = json["tracks"].toObject()["href"].toString();
    owner = json["owner"].toObject()["display_name"].toString();
    uri = json["uri"].toString();
  }
  PlayList *parent;
  QString id;
  QString name;
  QString img_url;
  QString tracks_href;
  QString owner;
  QString imgFileName;
  QString uri;
  QString averageCoverColor;
  QList<Track*> tracks;

  void loadTracksFromJson(QJsonObject json)
  {
    tracks.clear();
    for (auto item : json["items"].toArray()) {
      auto track = new Track(parent, item.toObject()["track"].toObject(), uri);
      tracks.append(track);
    }
  }

  void calculateAverageCoverColor()
  {
    if (imgFileName.isEmpty()) {
      qDebug() << "Album::calculateAverageCoverColor: imgFileName is empty";
      return;
    }
    QImage img(imgFileName);
    if (img.isNull()) {
      qDebug() << "Album::calculateAverageCoverColor: img is null";
      return;
    }
    int r = 0, g = 0, b = 0;
    int count = 0;
    for (int x = 0; x < img.width(); x += 10) {
      for (int y = 0; y < img.height(); y += 10) {
        QColor color = img.pixelColor(x, y);
        r += color.red();
        g += color.green();
        b += color.blue();
        count++;
      }
    }
    r /= count;
    g /= count;
    b /= count;
    averageCoverColor = QColor(r, g, b).name();
    qDebug() << "PlayList::calculateAverageCoverColor: " << averageCoverColor;
  }
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PlayList::PlayList(QObject *parent, QJsonObject json)
{
  impl.reset(new Implementation(this, json));
}

PlayList::~PlayList() {}

// Q_READ @@@@@@@@@@@@@@@@@@@@@@@@

const QString PlayList::type() const { return "playlist"; }
QString PlayList::id() const { return impl->id; }
QString PlayList::name() const { return impl->name; }
QString PlayList::img_url() const { return impl->img_url; }
QString PlayList::tracks_href() const { return impl->tracks_href; }
QString PlayList::owner() const { return impl->owner; }
QString& PlayList::imgFileName() { return impl->imgFileName; }
const QString& PlayList::uri() const { return impl->uri; }
QString& PlayList::averageCoverColor() { return impl->averageCoverColor; }

QQmlListProperty<Track> PlayList::tracks()
{
  return QQmlListProperty<Track>(this, &impl->tracks);
}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void PlayList::loadTracksFromJson(QJsonObject json)
{
  return impl->loadTracksFromJson(json);
}

void PlayList::calculateAverageCoverColor()
{
  return impl->calculateAverageCoverColor();
}

bool PlayList::isEmpty() const { return impl->tracks.isEmpty(); }

}}