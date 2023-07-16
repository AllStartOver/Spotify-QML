#pragma once

#include <QObject>
#include <QJsonObject>
#include <QScopedPointer>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QImage>
#include <QQmlListProperty>

#include "data/track.h"
#include "data/baseData.h"

namespace libspot {
namespace data {

class Track;

class PlayList : public BaseData
{
  Q_PROPERTY(QString type READ type CONSTANT)
  Q_PROPERTY(QString owner READ owner CONSTANT)
  Q_PROPERTY(QString tracks_href READ tracks_href CONSTANT)
  Q_PROPERTY(bool isPublic READ isPublic CONSTANT)
  Q_PROPERTY(QQmlListProperty<Track> tracks READ tracks CONSTANT)
public:
  explicit PlayList(QObject *parent, QJsonObject json);
  ~PlayList() override;

  // Q_READ @@@@@@@@@@@@@@@@@@@@@@@@
  const QString type() const;
  QString tracks_href() const;
  QString owner() const;
  bool isPublic() const;

  QQmlListProperty<Track> tracks();

  void loadTracksFromJson(QJsonObject json);

  bool isEmpty() const;

signals:
  void signalPlayListRequestTracksFinished();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}