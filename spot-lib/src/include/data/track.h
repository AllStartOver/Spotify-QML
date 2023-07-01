#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QScopedPointer>
#include <QList>
#include <QQmlListProperty>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFile>
#include "data/artist.h"
#include "data/playList.h"
#include "network/NetworkManager.h"

namespace libspot {
namespace data {

class Track : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString id READ id CONSTANT)
  Q_PROPERTY(QString name READ name CONSTANT)
  Q_PROPERTY(QString album READ album CONSTANT)
  Q_PROPERTY(QString album_id READ album_id CONSTANT)
  Q_PROPERTY(QString imgFileName READ imgFileName CONSTANT)
  Q_PROPERTY(QString img_url READ img_url CONSTANT)
  Q_PROPERTY(QString context_uri READ context_uri CONSTANT)
  Q_PROPERTY(int duration_ms READ duration_ms CONSTANT)
  Q_PROPERTY(QQmlListProperty<Artist> artists READ artists CONSTANT)
public:
  explicit Track(QObject* parent, QJsonObject json, QString& context_uri);
  explicit Track(QObject* parent, QJsonObject json);
  ~Track();

  // Q_READ @@@@@@@@@@@@@@@@@@@@@@@@
  QString id() const;
  QString name() const;
  QString album() const;
  const QString& album_id() const;
  const QString& imgFileName() const;
  const QString& img_url() const;
  const QString& context_uri() const;

  int duration_ms() const;

  QQmlListProperty<Artist> artists();

signals:
  void signalTrackRequestCover(const QString& ur);
  void signalTrackRequestCoverFinished();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}
