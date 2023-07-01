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
    for (auto track : json["tracks"].toObject()["items"].toArray()) {
      tracks.append(new Track(parent, track.toObject()));
    }
  }
  Album* parent;
  QString id;
  QString name;
  QString img_url;
  QString artist;
  QString imgFileName;
  QString uri;
  QList<Track*> tracks;
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

Album::Album(QObject* parent, QJsonObject json)
{
  impl.reset(new Implementation(this, json));
}

Album::~Album() {}

// Q_READ @@@@@@@@@@@@@@@@@@@@@@@@

const QString& Album::id() const { return impl->id; }
const QString& Album::name() const { return impl->name; }
const QString& Album::img_url() const { return impl->img_url; }
const QString& Album::imgFileName() const { return impl->imgFileName; }
const QString& Album::uri() const { return impl->uri; }

QQmlListProperty<Track> Album::tracks()
{
  return QQmlListProperty<Track>(this, &impl->tracks);
}

// MEMBER FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@

bool Album::isEmpty() const { return impl->tracks.isEmpty(); }

}}