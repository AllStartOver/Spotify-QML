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
    img_url = json["images"].toArray()[0].toObject()["url"].toString();
    tracks_href = json["tracks"].toObject()["href"].toString();
    owner = json["owner"].toObject()["display_name"].toString();
    qDebug() << "Playlist: " << name << " " << tracks_href;
  }
  PlayList *parent;
  QString id;
  QString name;
  QString img_url;
  QString tracks_href;
  QString owner;
  QString imgFileName;
  QList<Track*> tracks;

  void loadTracksFromJson(QJsonObject json)
  {
    for (auto item : json["items"].toArray()) {
      auto track = new Track(parent, item.toObject()["track"].toObject());
      tracks.append(track);
    }
    qDebug() << "Tracks loaded: " << tracks.size();
  }
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PlayList::PlayList(QObject *parent, QJsonObject json)
  : QObject(parent)
{
  impl.reset(new Implementation(this, json));
}

PlayList::~PlayList() {}

// Q_READ @@@@@@@@@@@@@@@@@@@@@@@@

QString PlayList::id() const { return impl->id; }
QString PlayList::name() const { return impl->name; }
QString PlayList::img_url() const { return impl->img_url; }
QString PlayList::tracks_href() const { return impl->tracks_href; }
QString PlayList::owner() const { return impl->owner; }
QString& PlayList::imgFileName() { return impl->imgFileName; }

QQmlListProperty<Track> PlayList::tracks()
{
  return QQmlListProperty<Track>(this, &impl->tracks);
}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void PlayList::loadTracksFromJson(QJsonObject json)
{
  return impl->loadTracksFromJson(json);
}

}}