#include "data/album.h"

namespace libspot {
namespace data {

class Album::Implementation
{
public:
  Implementation(Album* _parent, QJsonObject json)
    : parent(_parent)
  {
    id = json["id"].toString();
    name = json["name"].toString();
    img_url = json["images"].toArray()[0].toObject()["url"].toString();
    uri = json["uri"].toString();
    release_date = json["release_date"].toString();
    for (auto track : json["tracks"].toObject()["items"].toArray()) {
      tracks.append(new Track(parent, track.toObject(), uri));
    }
    for (auto artist : json["artists"].toArray()) {
      artists.append(new Artist(parent, artist.toObject()));
    }
    qDebug() << "Album::Implementation: tracks.size() = " << tracks.size() << " for album " << name;
  }
  Album* parent;
  QString id;
  QString name;
  QString img_url;
  QString imgFileName;
  QString uri;
  QString release_date;
  QString averageCoverColor;
  QList<Artist*> artists;
  QList<Track*> tracks;

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
    if(averageCoverColor != "") {
      qDebug() << "Album::calculateAverageCoverColor: averageCoverColor is already calculated";
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

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

Album::Album(QObject* parent, QJsonObject json)
  : QObject(parent)
{
  impl.reset(new Implementation(this, json));
}

Album::~Album() 
{
}

// Q_READ @@@@@@@@@@@@@@@@@@@@@@@@

const QString& Album::id() const { return impl->id; }
const QString& Album::name() const { return impl->name; }
const QString& Album::imgUrl() const { return impl->img_url; }
const QString& Album::uri() const { return impl->uri; }
const QString& Album::release_date() const { return impl->release_date; }
QString& Album::imgFileName() { return impl->imgFileName; }

const QString& Album::averageCoverColor() const { return impl->averageCoverColor; }

QQmlListProperty<Artist> Album::artists()
{
  return QQmlListProperty<Artist>(this, &impl->artists);
}

QQmlListProperty<Track> Album::tracks()
{
  return QQmlListProperty<Track>(this, &impl->tracks);
}

// MEMBER FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@

void Album::calculateAverageCoverColor()
{
  impl->calculateAverageCoverColor();
}

bool Album::isEmpty() const { return impl->tracks.isEmpty(); }

}}