#include "network/AuthServer.h"

namespace libspot {
namespace network {

class AuthServer::Implementation
{
public:
  Implementation(AuthServer *_parent) : parent(_parent) 
  {
    QTcpServer::connect(parent, &AuthServer::newConnection, parent, &AuthServer::onNewConnection);
  }

  // SLOTS
  void onNewConnection()
  {
    QTcpSocket *socket = parent->nextPendingConnection();
    socket->waitForReadyRead();
    QString response = QString(socket->readAll());

    // Unrealated request, ignore it
    if (!response.contains("?code=")) {
      socket->close();
      parent->close();
      emit parent->codeError(response);
      return;
    }

    // Extract the code from the response
    auto left = response.left(response.indexOf(QStringLiteral(" HTTP")));
	  auto code = left.right(left.length() - left.indexOf(QStringLiteral("?code=")) - 6);

    socket->flush();
    socket->waitForBytesWritten(TIMEOUT);
    socket->close();
    parent->close();

    emit parent->codeReceived(code);
  }

  AuthServer *parent;
  const int PORT = 8888;
  const int TIMEOUT = 3000;
};

AuthServer::AuthServer(QObject *parent) 
  : QTcpServer(parent)
{
  impl.reset(new Implementation(this));
}

AuthServer::~AuthServer() {}

bool AuthServer::listen() { return QTcpServer::listen(QHostAddress::LocalHost, impl->PORT);}

// SLOTS
void AuthServer::onNewConnection() { return impl->onNewConnection(); }

}}