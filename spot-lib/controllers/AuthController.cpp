#include "AuthController.h"

namespace libspot {
namespace controllers {

using namespace libspot::network;
class AuthController::Implementation
{
public:
  Implementation(QObject *_parent) : parent(_parent)
  {
    authServer = new AuthServer(parent);
    httpClientAuth = new HttpClientAuth(parent);
  }

  void openAuthPage() const
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

  // SLOTS 

  void onCodeReceived(QString code)
  {
    httpClientAuth->post(code, REDIRECT_URL, CLIENT_ID, CLIENT_SECRET);
  }

  void onTokenReceived(QString access_token, QString refresh_token)
  {

  }

  QObject* parent;
  AuthServer *authServer;
  HttpClientAuth *httpClientAuth; 
};

AuthController::AuthController(QObject *parent)
  : QObject(parent)
{
  impl.reset(new Implementation(this));
  connect(impl->authServer, &AuthServer::codeReceived, this, &AuthController::onCodeReceived);
  connect(impl->httpClientAuth, &HttpClientAuth::tokenReceived, this, &AuthController::onTokenReceived);
}

AuthController::~AuthController()
{
}

void AuthController::setupAuthorization()
{
  impl->authServer->listen();
}

void AuthController::openAuthPage() const
{
  return impl->openAuthPage();
}

// SLOTS

void AuthController::onCodeReceived(QString code)
{
  return impl->onCodeReceived(code);
}

void AuthController::onTokenReceived(QString access_token, QString refresh_token)
{
  return impl->onTokenReceived(access_token, refresh_token);
}

}}