#pragma once

#include <QObject>
#include <QJsonObject>
#include <QScopedPointer>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QQmlListProperty>

#include "data/track.h"
#include "data/album.h"

namespace libspot {
namespace data {

class Track;
class Album;

class ArtistPage : public QObject 
{
  Q_OBJECT
  Q_PROPERTY(QString type READ type CONSTANT)
  Q_PROPERTY(QString id READ id CONSTANT)
  Q_PROPERTY(QString name READ name CONSTANT)
  Q_PROPERTY(QString imgUrl READ imgUrl CONSTANT)
  Q_PROPERTY(QString imgFileName READ imgFileName CONSTANT)
  Q_PROPERTY(QString averageCoverColor READ averageCoverColor CONSTANT)
  Q_PROPERTY(QQmlListProperty<Track> topTracks READ topTracks CONSTANT)
  Q_PROPERTY(QQmlListProperty<Album> albums READ albums CONSTANT)
  Q_PROPERTY(QQmlListProperty<Album> singles READ singles CONSTANT)
  Q_PROPERTY(QQmlListProperty<Album> compilations READ compilations CONSTANT)
  Q_PROPERTY(QQmlListProperty<Album> appearsOn READ appearsOn CONSTANT)

public:
  explicit ArtistPage(QObject *parent, QJsonObject json);
  ~ArtistPage();

  // MEMBER FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@
  void addTopTracks(QJsonObject json);
  bool topTracksIsEmpty() const;
  bool albumsIsEmpty() const;
  Q_INVOKABLE void calculateAverageCoverColor();

  // Q_READ @@@@@@@@@@@@@@@@@@@@@@@@
  const QString type() const { return "artist"; }
  const QString& id() const;
  const QString& name() const;
  const QString& uri() const;
  const QString& imgUrl() const;
  QString& imgFileName();
  const QString& averageCoverColor() const;

  QQmlListProperty<Track> topTracks();
  QQmlListProperty<Album> albums();
  QQmlListProperty<Album> singles();
  QQmlListProperty<Album> compilations();
  QQmlListProperty<Album> appearsOn();

signals:
  void signalArtistPageRequestTopTracks(const QString& id);
  void signalArtistPageRequestCover(const QString& url, const QString& id);
  void signalArtistPageRequestCoverFinished();
  void signalArtistPageRequestTopTracksFinished();
  void signalArtistPageRequestAlbumsFinished();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}