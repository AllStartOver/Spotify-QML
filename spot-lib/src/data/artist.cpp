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
  QString imgUrl;
  QString uri;
  QString imgFileName;
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

const QString& Artist::id() const
{
  return impl->id;
}

const QString& Artist::name() const
{
  return impl->name;
}

const QString& Artist::imgUrl() const
{
  return impl->imgUrl;
}

const QString& Artist::uri() const
{
  return impl->uri;
}

QString& Artist::imgFileName()
{
  return impl->imgFileName;
}

}}