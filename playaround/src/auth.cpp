#include "auth.h"

Auth::Auth(QObject *parent) : QObject(parent)
{
}

Auth::~Auth()
{
}

auto Auth::get(const QString &code, 
    const QString &redirectUrl, 
    const QString &id, 
    const QString &secret) ->QString
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QUrl url("https://accounts.spotify.com/api/token");
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Authorization", "Basic " + QByteArray(QString("%1:%2").arg(id).arg(secret).toUtf8()).toBase64());

    QString data = QString("grant_type=authorization_code&code=%1&redirect_uri=%2")
        .arg(code)
        .arg(redirectUrl)
    ;
    QNetworkReply *reply = manager->post(request, data.toUtf8());
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QString response = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();

    QString access_token = jsonObject["access_token"].toString();
    QString refresh_token = jsonObject["refresh_token"].toString();

    std::cout << "access_token: " << access_token.toStdString() << std::endl;
    std::cout << "refresh_token: " << refresh_token.toStdString() << std::endl;
    return response;
}