#include "data/artistPage.h"

namespace libspot {
namespace data {

class ArtistPage::Implementation 
{
public:
  Implementation(ArtistPage* _parent, QJsonObject json)
    : parent(_parent)
  {
    id = json["id"].toString();
    name = json["name"].toString();
    uri = json["uri"].toString();
    QJsonArray images = json["images"].toArray();
    if (images.size() == 0) {
      qDebug() << "ArtistPage::Implementation: images.size() == 0";
      return;
    }
    imgUrl = images[0].toObject()["url"].toString();
  }

  ArtistPage* parent;
  QString id;
  QString name;
  QString uri;
  QString imgUrl;
  QString imgFileName;
  QString averageCoverColor;
  QList<Track*> topTracks;
  QList<Album*> albums;
  QList<Album*> singles;
  QList<Album*> compilations;
  QList<Album*> appearsOn;

  // MEMBER FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@
  void addTopTracks(QJsonObject json)
  {
    for (auto track : json["tracks"].toArray()) {
      topTracks.append(new Track(parent, track.toObject(), uri));
    }
  }
  void addAlbums(QJsonObject json)
  {
    for (auto album : json["items"].toArray()) {
      if (album.toObject()["album_type"].toString() == "album") {
        albums.append(new Album(parent, album.toObject()));
      }
      else if (album.toObject()["album_type"].toString() == "single") {
        singles.append(new Album(parent, album.toObject()));
      }
      else if (album.toObject()["album_type"].toString() == "compilation") {
        compilations.append(new Album(parent, album.toObject()));
      }
    }
    emit parent->signalArtistPageRequestAlbumsFinished();
  }

  void calculateAverageCoverColor()
  {
    if (imgFileName.isEmpty()) {
      qDebug() << "ArtistPage::calculateAverageCoverColor: imgFileName is empty";
      return;
    }
    QImage img(imgFileName);
    if (img.isNull()) {
      qDebug() << "ArtistPage::calculateAverageCoverColor: img is null";
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
    qDebug() << "ArtistPage::calculateAverageCoverColor: " << averageCoverColor;
  }
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

ArtistPage::ArtistPage(QObject* parent, QJsonObject json)
  : QObject(parent)
{
  impl.reset(new Implementation(this, json));
}

ArtistPage::~ArtistPage() {}

// MEMBER FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@

void ArtistPage::addTopTracks(QJsonObject json)
{
  return impl->addTopTracks(json);
}

bool ArtistPage::topTracksIsEmpty() const
{
  return impl->topTracks.isEmpty();
}

bool ArtistPage::albumsIsEmpty() const
{
  return impl->albums.isEmpty() && impl->singles.isEmpty() && impl->compilations.isEmpty();
}

void ArtistPage::calculateAverageCoverColor()
{
  return impl->calculateAverageCoverColor();
}

// Q_READ @@@@@@@@@@@@@@@@@@@@@@@@

const QString& ArtistPage::id() const 
{
  return impl->id;
}

const QString& ArtistPage::name() const 
{
  return impl->name;
}

const QString& ArtistPage::uri() const 
{
  return impl->uri;
}

const QString& ArtistPage::imgUrl() const 
{
  return impl->imgUrl;
}

QString& ArtistPage::imgFileName()
{
  return impl->imgFileName;
}

const QString& ArtistPage::averageCoverColor() const 
{
  return impl->averageCoverColor;
}

QQmlListProperty<Track> ArtistPage::topTracks() 
{
  return QQmlListProperty<Track>(this, &impl->topTracks);
}

QQmlListProperty<Album> ArtistPage::albums() 
{
  return QQmlListProperty<Album>(this, &impl->albums);
}

QQmlListProperty<Album> ArtistPage::singles() 
{
  return QQmlListProperty<Album>(this, &impl->singles);
}

QQmlListProperty<Album> ArtistPage::compilations() 
{
  return QQmlListProperty<Album>(this, &impl->compilations);
}

QQmlListProperty<Album> ArtistPage::appearsOn() 
{
  return QQmlListProperty<Album>(this, &impl->appearsOn);
}

}}