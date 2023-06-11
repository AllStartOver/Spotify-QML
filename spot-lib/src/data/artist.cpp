#include "data/artist.h"

namespace libspot {
namespace data {

class Artist::Implementation 
{
public:
  Implementation(Artist* _parent, QJsonObject json)
    : parent(_parent)
  {
    id = json["id"].toString();
    name = json["name"].toString();
  }

  Artist *parent;
  QString id;
  QString name;
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

Artist::Artist(QObject* parent, QJsonObject json)
  : QObject(parent)
{
  impl.reset(new Implementation(this, json));
}

Artist::~Artist() {}

// Q_READ @@@@@@@@@@@@@@@@@@@@@@@@

QString Artist::id() const
{
  return impl->id;
}

QString Artist::name() const
{
  return impl->name;
}

}}