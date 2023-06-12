#pragma once

#include <QObject>
#include <QJsonObject>
#include <QScopedPointer>

namespace libspot {
namespace data {

class PlayList : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString id READ id CONSTANT)
  Q_PROPERTY(QString name READ name CONSTANT)
public:
  explicit PlayList(QObject* parent, QJsonObject json);
  ~PlayList();

  // Q_READ @@@@@@@@@@@@@@@@@@@@@@@@
  QString id() const;
  QString name() const;

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}