#pragma once

#include <QObject>
#include <QSignalSpy>
#include <QDebug>

#include <gtest/gtest.h>
#include "controllers/AuthController.h"

using namespace libspot::controllers;

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
    authController = new AuthController();
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
  spy.wait(10000);
  EXPECT_EQ(spy.count(), 1);
  qDebug() << authController->getAccount()->access_token;
  qDebug() << authController->getAccount()->refresh_token;
}