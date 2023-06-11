#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QEventLoop>
#include <QDebug>

#include "controllers/AuthController.h"
#include "controllers/APIController.h"

#include "network/spotify-api/PlayerAPI.h"
#include "setting/account.h"

#include "data/artist.h"

using namespace libspot::controllers;
using namespace libspot::setting;
using namespace libspot::network::API;
using namespace libspot::data;

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine; 

  QString rootPath = QCoreApplication::applicationDirPath();
  Account account(rootPath);
  AuthController authController(nullptr, &account);

  if(!account.localFileExists()) 
  {
		authController.setupAuthorization();
		authController.openAuthPage();      
		QEventLoop loop;
		QObject::connect(&authController, &AuthController::authFinished, &loop, &QEventLoop::quit);
		loop.exec();
		account.saveToFile();
		qDebug() << "Auth finished";
  }
	else
	{
		account.readFromFile();
		authController.refreshAccessToken();
		QEventLoop loop;
		QObject::connect(&authController, &AuthController::authFinished, &loop, &QEventLoop::quit);
		loop.exec();
		qDebug() << "Refresh finished";
	}

  QString access_token = authController.getAccount()->access_token;
  PlayerAPI playerAPI(access_token);

  qmlRegisterType<PlayerAPI>("libspot", 1, 0, "PlayerAPI");
	qmlRegisterType<PlayerState>("libspot", 1, 0, "PlayerState");
	qmlRegisterType<Artist>("libspot", 1, 0, "Artist");

  // register types
	QString executablePath = QCoreApplication::applicationDirPath();
	qDebug() << executablePath;
	engine.rootContext()->setContextProperty("executablePath", executablePath);
  engine.rootContext()->setContextProperty("playerAPI", &playerAPI);
	engine.rootContext()->setContextProperty("playerState", &playerAPI.getPlayerState());
	// load qml
  engine.addImportPath(":/spotify-qml/imports");
  const QUrl url(u"qrc:/spotify-qml/imports/Views/qml/MainWindow.qml"_qs);
  engine.load(url);

  return app.exec();
}
