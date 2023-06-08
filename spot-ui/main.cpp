#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QEventLoop>
#include <QDebug>

#include "controllers/AuthController.h"
#include "controllers/APIController.h"

#include "network/spotify-api/PlayerAPI.h"
#include "setting/account.h"

using namespace libspot::controllers;
using namespace libspot::setting;
using namespace libspot::network::API;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine; 

    // Account account;
    // AuthController authController(nullptr, &account);

    // authController.setupAuthorization();
    // authController.openAuthPage();

    // QEventLoop loop;
    // QObject::connect(&authController, &AuthController::authFinished, &loop, &QEventLoop::quit);
    // loop.exec();

    // qDebug() << "Auth finished";

    // QString access_token = authController.getAccount()->access_token;
    // PlayerAPI playerAPI(access_token);

    // qmlRegisterType<PlayerAPI>("libspot.network.api", 1, 0, "PlayerAPI");

    // // register types
    // engine.rootContext()->setContextProperty("playerAPI", &playerAPI);
    engine.addImportPath(":/spotify-qml/imports");
    const QUrl url(u"qrc:/spotify-qml/imports/Views/qml/MainWindow.qml"_qs);
    engine.load(url);

    return app.exec();
}
