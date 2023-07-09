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
    qDebug() << "ArtistPage::Implementation: id: " << id << " name: " << name << " imgUrl: " << imgUrl;
  }

  ArtistPage* parent;
  QString id;
  QString name;
  QString imgUrl;
  QString imgFileName;
  QList<Track*> topTracks;
  QList<Album*> albums;
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

ArtistPage::ArtistPage(QObject* parent, QJsonObject json)
  : QObject(parent)
{
  impl.reset(new Implementation(this, json));
}

ArtistPage::~ArtistPage() {}

// Q_READ @@@@@@@@@@@@@@@@@@@@@@@@

const QString& ArtistPage::id() const 
{
  return impl->id;
}

const QString& ArtistPage::name() const 
{
  return impl->name;
}

const QString& ArtistPage::imgFileName() const 
{
  return impl->imgFileName;
}

QQmlListProperty<Track> ArtistPage::tracks() 
{
  return QQmlListProperty<Track>(this, &impl->topTracks);
}

}}