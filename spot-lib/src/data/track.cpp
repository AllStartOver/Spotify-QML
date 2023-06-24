#include "data/track.h"

namespace libspot {
namespace data {

class Track::Implementation 
{
public:
  Implementation(Track* _parent, QJsonObject json)
    : parent(_parent)
  {
    id = json["id"].toString();
    name = json["name"].toString();
    album = json["album"].toObject()["name"].toString();
    duration_ms = json["duration_ms"].toInt();
    for (auto artist : json["artists"].toArray()) {
      artists.append(new Artist(parent, artist.toObject()));
    }
  }
  Track *parent;
  QString id;
  QString name;
  QString album;
  QString img_url;
  int duration_ms;
  QList<Artist*> artists;
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

Track::Track(QObject *parent, QJsonObject json)
  : QObject(parent)
{
  impl.reset(new Implementation(this, json));
}

Track::~Track() {}

QString Track::id() const { return impl->id; }
QString Track::name() const { return impl->name; }
QString Track::album() const { return impl->album; }
int Track::duration_ms() const { return impl->duration_ms; }

QQmlListProperty<Artist> Track::artists()
{
  return QQmlListProperty<Artist>(this, &impl->artists);
}

}}