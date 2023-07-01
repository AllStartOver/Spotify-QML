#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QEventLoop>
#include <QDebug>

#include "controllers/AuthController.h"
#include "controllers/APIController.h"
#include "controllers/ViewController.h"

#include "network/spotify-api/PlayerAPI.h"
#include "network/spotify-api/PlayListsAPI.h"
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

	APIController::instance()->init(access_token);
	ViewController* viewController = new ViewController();

  qmlRegisterType<PlayerAPI>("libspot", 1, 0, "PlayerAPI");
	qmlRegisterType<PlayListsAPI>("libspot", 1, 0, "PlayListsAPI");
	qmlRegisterType<PlayerState>("libspot", 1, 0, "PlayerState");
	qmlRegisterType<Artist>("libspot", 1, 0, "Artist");

  // register types
	QString executablePath = QCoreApplication::applicationDirPath();
	engine.rootContext()->setContextProperty("executablePath", executablePath);
  engine.rootContext()->setContextProperty("playerAPI", APIController::instance()->getPlayerAPI());
	engine.rootContext()->setContextProperty("playerState", &APIController::instance()->getPlayerAPI()->getPlayerState());
	engine.rootContext()->setContextProperty("playListsAPI", APIController::instance()->getPlayListsAPI());
	engine.rootContext()->setContextProperty("albumAPI", APIController::instance()->getAlbumAPI());
	engine.rootContext()->setContextProperty("viewController", viewController);
	// load qml
  engine.addImportPath(":/spotify-qml/imports");
  const QUrl url(u"qrc:/spotify-qml/imports/Views/qml/MainWindow.qml"_qs);
  engine.load(url);

  return app.exec();
}
