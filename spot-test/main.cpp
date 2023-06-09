#include <QGuiApplication>
#include <QCoreApplication>
#include <gtest/gtest.h>

#include "controllers/AuthController.h"
#include "setting/account.h"

// #include "testsuite/network/AuthServer.h"
// #include "testsuite/network/HttpAuthClient.h"
// #include "testsuite/controllers/AuthControllerTest.h"
// #include "testsuite/setting/AccountTest.h"
#include "testsuite/network/spotify-api/PlayerAPITest.h"

// #include "controllers/AuthController.h"

using namespace libspot::controllers;
using namespace libspot::setting;

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  QCoreApplication app(argc, argv);

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

  return RUN_ALL_TESTS();
}
