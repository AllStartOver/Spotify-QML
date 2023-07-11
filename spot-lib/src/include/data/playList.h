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

namespace libspot {
namespace data {

class Track;

class PlayList : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString type READ type CONSTANT)
  Q_PROPERTY(QString id READ id CONSTANT)
  Q_PROPERTY(QString name READ name CONSTANT)
  Q_PROPERTY(QString owner READ owner CONSTANT)
  Q_PROPERTY(QString img_url READ img_url CONSTANT)
  Q_PROPERTY(QString imgFileName READ imgFileName CONSTANT)
  Q_PROPERTY(QString tracks_href READ tracks_href CONSTANT)
  Q_PROPERTY(QString uri READ uri CONSTANT)
  Q_PROPERTY(QString averageCoverColor READ averageCoverColor CONSTANT)
  Q_PROPERTY(QQmlListProperty<Track> tracks READ tracks CONSTANT)
public:
  explicit PlayList(QObject *parent, QJsonObject json);
  ~PlayList();

  // Q_READ @@@@@@@@@@@@@@@@@@@@@@@@
  const QString type() const;
  QString id() const;
  QString name() const;
  QString img_url() const;
  QString tracks_href() const;
  QString owner() const;
  QString& imgFileName();
  const QString& uri() const;
  QString& averageCoverColor();

  QQmlListProperty<Track> tracks();

  void loadTracksFromJson(QJsonObject json);

  Q_INVOKABLE void calculateAverageCoverColor();

  bool isEmpty() const;

signals:
  void signalPlayListRequestTracks(const QString& id);
  void signalPlayListRequestCover(const QString& url, const QString& id);
  void signalPlayListRequestCoverFinished();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}