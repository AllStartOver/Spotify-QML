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
  QString imgUrl;
  QString imgFileName;
  QList<Track*> topTracks;
  QList<Album*> albums;
  QList<Album*> singles;
  QList<Album*> compilations;
  QList<Album*> appearsOn;

  // MEMBER FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@
  void addTopTracks(QJsonObject json)
  {
    for (auto track : json["tracks"].toArray()) {
      topTracks.append(new Track(parent, track.toObject()));
    }
    emit parent->signalArtistPageRequestTopTracksFinished();
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

void ArtistPage::addTopTrack(QJsonObject json)
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

// Q_READ @@@@@@@@@@@@@@@@@@@@@@@@

const QString& ArtistPage::id() const 
{
  return impl->id;
}

const QString& ArtistPage::name() const 
{
  return impl->name;
}

const QString& ArtistPage::imgUrl() const 
{
  return impl->imgUrl;
}

QString& ArtistPage::imgFileName()
{
  return impl->imgFileName;
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