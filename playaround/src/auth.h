#pragma once

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QString>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>
#include <string>

class Auth: public QObject
{
    Q_OBJECT

public:

    explicit Auth(QObject *parent = nullptr);
    ~Auth() override;

    auto get(const QString &code, 
        const QString &redirectUrl, 
        const QString &id, 
        const QString &secret) ->QString;
};
