#ifndef AUTHSERVER_H
#define AUTHSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDesktopServices>
#include <QUrl>
#include <QString>

#include <Windows.h>
#include <shellapi.h>

#include <vector>
#include <string>
#include <iostream>
#include <fmt/core.h>

#include "auth.h"

class AuthServer : public QTcpServer
{
  Q_OBJECT

public: 
  AuthServer(QObject *parent = 0);
  ~AuthServer();

  auto listen() -> bool;
  static auto redirectUrl() -> QString;
  void openUrl() const;

signals:
  void success();
  void failed(const QString &message);

public slots:
  void onNewConnection();

private:
  static const int PORT = 8888;
  static const int writeTimeout = 3000;

  const QString client_id = QString("92f036ac89bc4899921c9a20b85bce4a");
  const QString client_secret = QString("1d38b76e3d064049b065029e0c0e1207");
  Auth *auth = new Auth(nullptr);
};

#endif // AUTHSERVER_H