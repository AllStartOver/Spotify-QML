#include "controllers/AuthController.h"
#include "network/spotify-api/PlayerAPI.h"

namespace libspot {
namespace controllers {

using namespace libspot::network;
class AuthController::Implementation
{
public:
  Implementation(AuthController *_parent, Account *_account) 
    : parent(_parent),
      account(_account)
  {
    authServer = new AuthServer(_parent);
    httpClientAuth = new HttpClientAuth(_parent, _account);
  }

  void setupAuthorization()
  {
    if (!authServer->isListening()) {
      authServer->listen();
    }
  }

  void openAuthPage() const
  {
    if (!authServer->isListening()) {
      qDebug() << "AuthServer is not listening";
      return;
    }
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
      qDebug() << "Please open the following URL in your browser: " << url;

    #endif
  }

  void refreshAccessToken()
  {
    httpClientAuth->refresh_post(account->refresh_token, CLIENT_ID, CLIENT_SECRET);
  }

  // SLOTS 

  void onCodeReceived(QString code)
  {
    httpClientAuth->token_post(code, REDIRECT_URL, CLIENT_ID, CLIENT_SECRET);
  }

  void onTokenReceived(QString access_token, QString refresh_token)
  {
    account->access_token = access_token;
    account->refresh_token = refresh_token;
    emit parent->authFinished();
  }

  void onTokenRefreshed(QString access_token)
  {
    account->access_token = access_token;
    emit parent->authFinished();
  }

  AuthController* parent;
  AuthServer *authServer;
  HttpClientAuth *httpClientAuth; 
  Account *account;
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

AuthController::AuthController(QObject *parent, Account *account)
  : QObject(parent)
{
  impl.reset(new Implementation(this, account));
  connect(impl->authServer, &AuthServer::codeReceived, this, &AuthController::onCodeReceived);
  connect(impl->httpClientAuth, &HttpClientAuth::tokenReceived, this, &AuthController::onTokenReceived);
  connect(impl->httpClientAuth, &HttpClientAuth::tokenUpdated, this, &AuthController::onTokenRefreshed);
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

void AuthController::refreshAccessToken()
{
  return impl->refreshAccessToken();
}

Account* AuthController::getAccount() const
{
  return impl->account;
}

// SLOTS //

void AuthController::onCodeReceived(QString code)
{
  return impl->onCodeReceived(code);
}

void AuthController::onTokenReceived(QString access_token, QString refresh_token)
{
  return impl->onTokenReceived(access_token, refresh_token);
}

void AuthController::onTokenRefreshed(QString access_token)
{
  return impl->onTokenRefreshed(access_token);
}

bool AuthController::isAuthServerListening() const
{
  return impl->authServer->isListening();
}
}}