#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QScopedPointer>
#include <QList>
#include <QQmlListProperty>

#include "data/artist.h"

namespace libspot {
namespace data {

class Track : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString id READ id CONSTANT)
  Q_PROPERTY(QString name READ name CONSTANT)
  Q_PROPERTY(QString album READ album CONSTANT)
  Q_PROPERTY(int duration_ms READ duration_ms CONSTANT)
  Q_PROPERTY(QQmlListProperty<Artist> artists READ artists CONSTANT)
public:
  explicit Track(QObject* parent, QJsonObject json);
  ~Track();

  // Q_READ @@@@@@@@@@@@@@@@@@@@@@@@
  QString id() const;
  QString name() const;
  QString album() const;
  int duration_ms() const;

  QQmlListProperty<Artist> artists();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}
