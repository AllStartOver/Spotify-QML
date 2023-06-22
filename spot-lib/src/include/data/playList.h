#pragma once

#include <QObject>
#include <QJsonObject>
#include <QScopedPointer>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>

#include "data/track.h"

namespace libspot {
namespace data {

class PlayList : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString id READ id CONSTANT)
  Q_PROPERTY(QString name READ name CONSTANT)
public:
  explicit PlayList(QObject* parent, QJsonObject json);
  ~PlayList();

  // Q_READ @@@@@@@@@@@@@@@@@@@@@@@@
  QString id() const;
  QString name() const;
  QString img_url() const;
  QString tracks_href() const;

  void loadTracksFromJson(QJsonObject json);

signals:
  void signalPlayListRequestTracks(const QString &id);

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}