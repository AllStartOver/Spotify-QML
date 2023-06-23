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

class PlayList : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString id READ id CONSTANT)
  Q_PROPERTY(QString name READ name CONSTANT)
  Q_PROPERTY(QString owner READ owner CONSTANT)
  Q_PROPERTY(QString img_url READ img_url CONSTANT)
  Q_PROPERTY(QString imgFileName READ imgFileName CONSTANT)
public:
  explicit PlayList(QObject* parent, QJsonObject json);
  ~PlayList();

  // Q_READ @@@@@@@@@@@@@@@@@@@@@@@@
  QString id() const;
  QString name() const;
  QString img_url() const;
  QString tracks_href() const;
  QString owner() const;
  QString& imgFileName();

  QQmlListProperty<Track> tracks();

  void loadTracksFromJson(QJsonObject json);

signals:
  void signalPlayListRequestTracks(const QString& id);
  void signalPlayListRequestCover(const QString& url, const QString& id);
  void signalPlayListRequestCoverFinished();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}