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
    qDebug() << "Playlist: " << name << " " << tracks_href;
  }
  PlayList *parent;
  QString id;
  QString name;
  QString img_url;
  QString tracks_href;
  QList<Track*> tracks;

  void loadTracksFromJson(QJsonObject json)
  {
    for (auto item : json["items"].toArray()) {
      auto track = new Track(parent, item.toObject()["track"].toObject());
      tracks.append(track);
    }
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

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void PlayList::loadTracksFromJson(QJsonObject json)
{
  return impl->loadTracksFromJson(json);
}

}}