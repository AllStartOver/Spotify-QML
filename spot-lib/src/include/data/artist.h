
#pragma once 

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QScopedPointer>
#include <QFile>
#include <QNetworkReply>

#include "network/NetworkManager.h"

namespace libspot {
namespace data {

class Artist : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString id READ id CONSTANT)
  Q_PROPERTY(QString name READ name CONSTANT)
  Q_PROPERTY(QString imgUrl READ imgUrl CONSTANT)
  Q_PROPERTY(QString uri READ uri CONSTANT)
  Q_PROPERTY(QString imgFileName READ imgFileName CONSTANT)
public:
  Artist(QObject* parent = nullptr, QJsonObject json = QJsonObject());
  ~Artist();

  // Q_READ @@@@@@@@@@@@@@@@@@@@@@@@
  const QString& id() const;
  const QString& name() const;
  const QString& imgUrl() const;
  const QString& uri() const;
  QString& imgFileName();  

  // MEMBER FUNCTIONS @@@@@@@@@@@@@@@@@@@
  Q_INVOKABLE void requestArtistImage();
signals:
  void signalRequestArtistImageFinished();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}