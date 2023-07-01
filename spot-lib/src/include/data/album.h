#pragma once

#include <QObject>
#include <QJsonObject>
#include <QScopedPointer>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QQmlListProperty>

#include "data/track.h"

namespace libspot {
namespace data {

class Track;

class Album : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString id READ id CONSTANT)
  Q_PROPERTY(QString name READ name CONSTANT)
  Q_PROPERTY(QString img_url READ img_url CONSTANT)
  Q_PROPERTY(QString imgFileName READ imgFileName CONSTANT)
  Q_PROPERTY(QString uri READ uri CONSTANT)
  Q_PROPERTY(QQmlListProperty<Track> tracks READ tracks CONSTANT)
public:
  explicit Album(QObject *parent, QJsonObject json);
  ~Album();

  // Q_READ @@@@@@@@@@@@@@@@@@@@@@@@
  const QString& id() const;
  const QString& name() const;
  const QString& img_url() const;
  const QString& imgFileName() const;
  const QString& uri() const;

  QQmlListProperty<Track> tracks();

  // MEMBER FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@

  bool isEmpty() const;

signals:
  void signalAlbumRequestTracks(const QString& id);
  void signalAlbumRequestCover(const QString& url, const QString& id);
  void signalAlbumRequestCoverFinished();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};


}}