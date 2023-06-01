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

  void processReply()
  {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(parent->sender());
    if (reply->error() != QNetworkReply::NoError) {
      qDebug() << "Error: " << reply->errorString();
      return;
    }

    QString response = QString(reply->readAll());
    reply->deleteLater();
  }

  HttpClientAuth *parent;
  QNetworkAccessManager *manager;
};

HttpClientAuth::HttpClientAuth(QObject *parent)
  : QObject(parent)
{
  impl.reset(new Implementation(this));
  QObject::connect(impl->manager, &QNetworkAccessManager::finished, this, &HttpClientAuth::processReply);
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

void HttpClientAuth::processReply()
{
  return impl->processReply();
}

}}