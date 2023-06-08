#pragma once

#include <QObject>
#include <QSignalSpy>
#include <QDebug>

#include <gtest/gtest.h>
#include "controllers/AuthController.h"
#include "setting/account.h"

using namespace libspot::controllers;
using namespace libspot::setting;

class AuthControllerTest : public testing::Test {

protected:

  static void SetupTestCase()
  {
    qDebug() << "TESTING AuthController...";
  }

  static void TearDownTestCase()
  {
    qDebug() << "DONE TESTING AuthController...";
  }

  virtual void SetUp() override
  {
    Account *account = new Account();
    authController = new AuthController(nullptr, account);
  }

  virtual void TearDown() override
  {
    delete authController;
  }

  AuthController *authController;
};

TEST_F(AuthControllerTest, checkIsListeningWithoutSetup)
{
  EXPECT_EQ(authController->isAuthServerListening(), false);
}

TEST_F(AuthControllerTest, checkIsListeningAfterSetup)
{
  authController->setupAuthorization();
  EXPECT_EQ(authController->isAuthServerListening(), true);
}

TEST_F(AuthControllerTest, checkAuthReceived)
{
  authController->setupAuthorization();
  authController->openAuthPage();
  QSignalSpy spy(authController, SIGNAL(authFinished()));
  spy.wait(5000);
  EXPECT_EQ(spy.count(), 1);
  QString path = QCoreApplication::applicationDirPath() + "/setting" + "/account.json";
  authController->getAccount()->saveToFile(path);
}

TEST_F(AuthControllerTest, checkAuthRefeshed)
{
  authController->setupAuthorization();
  QString path = QCoreApplication::applicationDirPath() + "/setting" + "/account.json";
  authController->getAccount()->readFromFile(path);
  qDebug() << authController->getAccount()->access_token;
  qDebug() << authController->getAccount()->refresh_token;
  qDebug() << "---------------";
  authController->refreshAccessToken();

  QSignalSpy spy(authController, SIGNAL(authFinished()));
  spy.wait(5000);
  EXPECT_EQ(spy.count(), 1);

  qDebug() << authController->getAccount()->access_token;
  qDebug() << authController->getAccount()->refresh_token;
  authController->getAccount()->saveToFile(path);

  qDebug() << "---------------";
  authController->refreshAccessToken();
  spy.wait(5000);
  EXPECT_EQ(spy.count(), 2);
  qDebug() << authController->getAccount()->access_token;
  qDebug() << authController->getAccount()->refresh_token;
  authController->getAccount()->saveToFile(path);
}