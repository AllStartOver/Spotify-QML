#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QScopedPointer>
#include <QUrl>
#include <QString>
#include <QVector>
#include <QDebug>
#include "HttpClientAuth.h"
#include "libSpotify_global.h"

namespace libspot {
namespace network {

class LIBSPOTIFYSHARED_EXPORT AuthServer : public QTcpServer
{
  Q_OBJECT
public: 
  AuthServer(QObject *parent = 0);
  ~AuthServer();

  bool listen();

signals:
  void codeReceived(QString code);
  void codeError(QString error);

public slots:
  void onNewConnection();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}

