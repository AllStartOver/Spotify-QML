#include "data/playList.h"

namespace libspot {
namespace data {

class PlayList::Implementation 
{
public:
  Implementation(PlayList *_parent, QJsonObject json)
    : parent(_parent)
  {
    tracks_href = json["tracks"].toObject()["href"].toString();
    owner = json["owner"].toObject()["display_name"].toString();
    isPublic = json["public"].toBool();
  }
  PlayList *parent;
  QString tracks_href;
  QString owner;
  bool isPublic;
  QList<Track*> tracks;

  void loadTracksFromJson(QJsonObject json)
  {
    tracks.clear();
    for (auto item : json["items"].toArray()) {
      auto track = new Track(parent, item.toObject()["track"].toObject());
      tracks.append(track);
    }
  }
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PlayList::PlayList(QObject *parent, QJsonObject json)
  : BaseData(parent, json)  
{
  impl.reset(new Implementation(this, json));
}

PlayList::~PlayList() {}

// Q_READ @@@@@@@@@@@@@@@@@@@@@@@@

const QString PlayList::type() const { return "playlist"; }
QString PlayList::tracks_href() const { return impl->tracks_href; }
QString PlayList::owner() const { return impl->owner; }
bool PlayList::isPublic() const { return impl->isPublic; }

QQmlListProperty<Track> PlayList::tracks()
{
  return QQmlListProperty<Track>(this, &impl->tracks);
}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void PlayList::loadTracksFromJson(QJsonObject json)
{
  return impl->loadTracksFromJson(json);
}

bool PlayList::isEmpty() const { return impl->tracks.isEmpty(); }

}}