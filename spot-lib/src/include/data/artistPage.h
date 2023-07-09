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
  Q_PROPERTY(QString id READ id CONSTANT)
  Q_PROPERTY(QString name READ name CONSTANT)
  Q_PROPERTY(QString imgFileName READ imgFileName CONSTANT)

public:
  explicit ArtistPage(QObject *parent, QJsonObject json);
  ~ArtistPage();

  // MEMBER FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@

  // Q_READ @@@@@@@@@@@@@@@@@@@@@@@@

  const QString& id() const;
  const QString& name() const;
  const QString& imgFileName() const;  

  QQmlListProperty<Track> tracks();

signals:
  void signalArtistPageRequestTopTracks(const QString& id);
  void signalArtistPageRequestCover(const QString& url, const QString& id);
  void signalArtistPageRequestCoverFinished();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}