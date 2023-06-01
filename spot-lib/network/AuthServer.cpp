#include "AuthServer.h"

namespace libspot {
namespace network {

class AuthServer::Implementation
{
public:
  Implementation(AuthServer *_parent) : parent(_parent) 
  {
    client = new HttpClientAuth(parent);
  }

  bool listen()
  {
    return parent->QTcpServer::listen(QHostAddress::LocalHost, PORT);
  }

  void onNewConnection()
  {
    QTcpSocket *socket = parent->nextPendingConnection();
    socket->waitForReadyRead();
    QString response = QString(socket->readAll());

    // Unrealated request, ignore it
    if (!response.contains("?code=")) {
      socket->close();
      return;
    }

    // Extract the code from the response

    auto left = response.left(response.indexOf(QStringLiteral(" HTTP")));
	  auto code = left.right(left.length() - left.indexOf(QStringLiteral("?code=")) - 6);

    socket->flush();
    socket->waitForBytesWritten(TIMEOUT);
    socket->close();
    parent->close();

    CODE = code;
    emit parent->codeReceived(CODE, REDIRECT_URL, CLIENT_ID, CLIENT_SECRET);
  }

  void openAuthUrl() const 
  {
    const QString scopeStr = SCOPES.join("%20") + "%20";
    const QString url = AUTH_BASE_RUL + QString("?client_id=%1&response_type=code&redirect_uri=%2&scope=%3")
      .arg(CLIENT_ID)
      .arg(REDIRECT_URL)
      .arg(scopeStr)
    ;

    // Open the Auth PAGE in the default browser
    #ifdef WINDOWS
      ShellExecuteA(0, 0, url.toStdString().c_str(), 0, 0, SW_SHOW);
    #endif

    #ifdef MACOS
    #endif
  }

  AuthServer *parent;
  HttpClientAuth *client = new HttpClientAuth(parent);
  const int PORT = 8888;
  const int TIMEOUT = 3000;
  const QString REDIRECT_URL = QString("http://localhost:%1").arg(PORT);
  QString CODE;
};

AuthServer::AuthServer(QObject *parent) 
  : QTcpServer(parent)
{
  impl.reset(new Implementation(this));
  QTcpServer::connect(this, &QTcpServer::newConnection, this, &AuthServer::onNewConnection);
  QTcpServer::connect(this, &AuthServer::codeReceived, this, &AuthServer::close);
  QObject::connect(this, &AuthServer::codeReceived, impl->client, &HttpClientAuth::post);
  QObject::connect(impl->client, &HttpClientAuth::tokenReceived, this, &AuthServer::tokenReceived);
}

AuthServer::~AuthServer() {}

bool AuthServer::listen() { return impl->listen(); }

void AuthServer::onNewConnection() { return impl->onNewConnection(); }


void AuthServer::openAuthUrl() const
{
  return impl->openAuthUrl();
}

const QString& AuthServer::getCode() const
{
  return impl->CODE;
}

}}