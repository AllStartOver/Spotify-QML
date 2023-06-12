#include "data/playList.h"

namespace libspot {
namespace data {

class PlayList::Implementation 
{
public:
  Implementation(PlayList* _parent, QJsonObject json)
    : parent(_parent)
  {
    id = json["id"].toString();
    name = json["name"].toString();
    qDebug() << name;
  }
  QObject *parent;
  QString id;
  QString name;
};

PlayList::PlayList(QObject* parent, QJsonObject json)
  : QObject(parent)
{
  impl.reset(new Implementation(this, json));
}

PlayList::~PlayList() {}

}}