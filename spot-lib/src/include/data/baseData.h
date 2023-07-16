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
#include <QImage>
#include <QFile>

#include "network/NetworkManager.h"

namespace libspot {
namespace data {

class BaseData : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString id READ id CONSTANT)
  Q_PROPERTY(QString name READ name CONSTANT)
  Q_PROPERTY(QString uri READ uri CONSTANT)
  Q_PROPERTY(QString imgFileName READ imgFileName CONSTANT)
  Q_PROPERTY(QString averageCoverColor READ averageCoverColor CONSTANT)

public:
  explicit BaseData(QObject* parent, QJsonObject json);
  virtual ~BaseData();

  // Q_READ @@@@@@@@@@@@@@@@@@@@@
  const QString& id() const;
  const QString& name() const;
  const QString& uri() const;
  const QString& imgFileName() const;
  const QString& averageCoverColor() const;

  // MEMBER FUNCS @@@@@@@@@@@@@@@@@@@@@
  Q_INVOKABLE void requestImage(bool highRes = true);
  Q_INVOKABLE void calculateAverageCoverColor();

signals:
  void signalRequestImageFinished();

private: 
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}
