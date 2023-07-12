#pragma once

#include <QObject>
#include <QJsonObject>
#include <QScopedPointer>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QQmlListProperty>

#include "data/track.h"
#include "data/artist.h"

namespace libspot {
namespace data {

class Track;
class Arist;

class Album : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString type READ type CONSTANT)
  Q_PROPERTY(QString id READ id CONSTANT)
  Q_PROPERTY(QString name READ name CONSTANT)
  Q_PROPERTY(QString imgUrl READ imgUrl CONSTANT)
  Q_PROPERTY(QString imgFileName READ imgFileName CONSTANT)
  Q_PROPERTY(QString uri READ uri CONSTANT)
  Q_PROPERTY(QString release_date READ release_date CONSTANT)
  Q_PROPERTY(QString averageCoverColor READ averageCoverColor CONSTANT)
  Q_PROPERTY(QQmlListProperty<Artist> artists READ artists CONSTANT)
  Q_PROPERTY(QQmlListProperty<Track> tracks READ tracks CONSTANT)
public:
  explicit Album(QObject *parent, QJsonObject json);
  ~Album();

  // Q_READ @@@@@@@@@@@@@@@@@@@@@@@@
  const QString type() const { return "album"; }
  const QString& id() const;
  const QString& name() const;
  const QString& imgUrl() const;
  const QString& uri() const;
  const QString& release_date() const;
  QString& imgFileName();
  const QString& averageCoverColor() const;

  QQmlListProperty<Artist> artists();
  QQmlListProperty<Track> tracks();

  // MEMBER FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@

  Q_INVOKABLE void calculateAverageCoverColor();

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