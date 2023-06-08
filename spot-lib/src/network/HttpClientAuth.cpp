#include "network/HttpClientAuth.h"
namespace libspot {
namespace network {

inline const QUrl URL_TOKEN = QUrl("https://accounts.spotify.com/api/token");

class HttpClientAuth::Implementation
{
public:
  Implementation(HttpClientAuth *_parent, Account *_account) 
    : parent(_parent),
      account(_account)
  {
    manager = new QNetworkAccessManager(parent);
  }

  void token_post(
    const QString code,
    const QString redirect_url,
    const QString client_id,
    const QString client_secret
  )
  {
    QNetworkRequest request;
    request.setUrl(URL_TOKEN);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Authorization", "Basic " + 
    QByteArray(QString("%1:%2").arg(client_id).arg(client_secret).toUtf8()).toBase64());

    QString data = QString("grant_type=authorization_code&code=%1&redirect_uri=%2")
      .arg(code)
      .arg(redirect_url)
    ;
    QNetworkReply *reply = manager->post(request, data.toUtf8());
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply=reply, this]() { onTokenReply(reply); });
  }

  void refresh_post(
    const QString refresh_token,
    const QString client_id,
    const QString client_secret
  )
  {
    QNetworkRequest request;
    request.setUrl(URL_TOKEN);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Authorization", "Basic " + 
    QByteArray(QString("%1:%2").arg(client_id).arg(client_secret).toUtf8()).toBase64());

    QString data = QString("grant_type=refresh_token&refresh_token=%1")
      .arg(refresh_token)
    ;
    QNetworkReply *reply = manager->post(request, data.toUtf8());
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply=reply, this]() { onRefreshReply(reply); });
  }

  void onTokenReply(QNetworkReply *reply)
  {
    if (reply->error() != QNetworkReply::NoError) {
      emit parent->tokenExpired();
      return;
    }
    QString response = reply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(response.toUtf8());  
    QJsonObject jsonObject = json.object();

    QString access_token = jsonObject["access_token"].toString();
    QString refresh_token = jsonObject["refresh_token"].toString();

    account->access_token = access_token;
    account->refresh_token = refresh_token;
    emit parent->tokenReceived(access_token, refresh_token);
  }

  void onRefreshReply(QNetworkReply *reply)
  {
    if (reply->error() != QNetworkReply::NoError) {
      emit parent->tokenExpired();
      return;
    }
    QString response = reply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(response.toUtf8());  
    QJsonObject jsonObject = json.object();

    QString access_token = jsonObject["access_token"].toString();

    account->access_token = access_token;

    emit parent->tokenUpdated(access_token);
  }

  HttpClientAuth *parent;
  QNetworkAccessManager *manager;
  Account *account;
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

HttpClientAuth::HttpClientAuth(QObject *parent, Account *account)
  : QObject(parent)
{
  impl.reset(new Implementation(this, account));
}

HttpClientAuth::~HttpClientAuth()
{
}

void HttpClientAuth::token_post(
  const QString code, 
  const QString redirect_url,
  const QString client_id,
  const QString client_secret
)
{
  return impl->token_post(code, redirect_url, client_id, client_secret);
}

void HttpClientAuth::refresh_post(
  const QString refresh_token,
  const QString client_id,
  const QString client_secret
)
{
  return impl->refresh_post(refresh_token, client_id, client_secret);
}

// SLOTS
void HttpClientAuth::onTokenReply(QNetworkReply *reply)
{
  return impl->onTokenReply(reply);
}

void HttpClientAuth::onRefreshReply(QNetworkReply *reply)
{
  return impl->onRefreshReply(reply);
}

}}