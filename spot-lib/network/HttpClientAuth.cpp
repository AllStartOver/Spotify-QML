#include "HttpClientAuth.h"

namespace libspot {
namespace network {

const QUrl URL_TOKEN = QUrl("https://accounts.spotify.com/api/token");

class HttpClientAuth::Implementation
{
public:
  Implementation(HttpClientAuth *_parent) : parent(_parent) 
  {
    manager = new QNetworkAccessManager(parent);
  }

  void post(
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
    manager->post(request, data.toUtf8());
  }

  void processReply(QNetworkReply *reply)
  {
    QString response = reply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(response.toUtf8());  
    QJsonObject jsonObject = json.object();

    QString access_token = jsonObject["access_token"].toString();
    QString refresh_token = jsonObject["refresh_token"].toString();

    qDebug() << "access_token: " << access_token;
    qDebug() << "refresh_token: " << refresh_token;
    
    emit parent->tokenReceived(access_token, refresh_token);
  }

  HttpClientAuth *parent;
  QNetworkAccessManager *manager;
  QString access_token;
  QString refresh_token;
};

HttpClientAuth::HttpClientAuth(QObject *parent)
  : QObject(parent)
{
  impl.reset(new Implementation(this));
  connect(impl->manager, &QNetworkAccessManager::finished, this, &HttpClientAuth::processReply);
}

HttpClientAuth::~HttpClientAuth()
{
}

void HttpClientAuth::post(
  const QString code, 
  const QString redirect_url,
  const QString client_id,
  const QString client_secret
)
{
  return impl->post(code, redirect_url, client_id, client_secret);
}

void HttpClientAuth::processReply(QNetworkReply *reply)
{
  return impl->processReply(reply);
}

}}