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
  }
  Track *parent;
  QString id;
  QString name;
  QString album;
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
}}