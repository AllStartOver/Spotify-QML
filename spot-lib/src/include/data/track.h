#pragma once

#include <QObject>
#include <QJsonObject>
#include <QScopedPointer>

namespace libspot {
namespace data {

class Track : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString id READ id CONSTANT)
  Q_PROPERTY(QString name READ name CONSTANT)
  Q_PROPERTY(QString album READ album CONSTANT)
public:
  explicit Track(QObject* parent, QJsonObject json);
  ~Track();

  // Q_READ @@@@@@@@@@@@@@@@@@@@@@@@
  QString id() const;
  QString name() const;
  QString album() const;

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}
