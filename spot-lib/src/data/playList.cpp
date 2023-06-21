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
    qDebug() << "Playlist: " << name;
  }
  PlayList *parent;
  QString id;
  QString name;
  QList<Track*> tracks;

  void fromJson(QJsonObject json)
  {
    qDebug() << name << ": " << json["items"].toArray().size();
  }

  void addFromJson(QJsonObject json)
  {
    qDebug() << name << ": " << json["items"].toArray().size();
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

QString PlayList::id() const { return impl->id; }
QString PlayList::name() const { return impl->name; }
void PlayList::fromJson(QJsonObject json) { return impl->fromJson(json); }
}}