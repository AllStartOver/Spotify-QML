
#pragma once 

#include <QObject>
#include <QJsonObject>
#include <QScopedPointer>

namespace libspot {
namespace data {

class Artist : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString id READ id CONSTANT)
  Q_PROPERTY(QString name READ name CONSTANT)
public:
  Artist(QObject* parent = nullptr, QJsonObject json = QJsonObject());
  ~Artist();
  // Q_READ @@@@@@@@@@@@@@@@@@@@@@@@
  QString id() const;
  QString name() const;
signals:

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}