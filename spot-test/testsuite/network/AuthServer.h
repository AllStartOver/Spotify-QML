#pragma once
#include <QObject>
#include <QSignalSpy>
#include <QDebug>
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "network/AuthServer.h"
#include "NetworkConfig.h"

#ifdef WINDOWS
  #include <Windows.h>
  #include <ShellApi.h>
#endif


using namespace libspot::network;

class AuthServerTest : public testing::Test {

protected:

  static void SetUpTestCase()
  {
    std::cout << "TESTING AuthServer..." << std::endl;
  }

  static void TearDownTestCase()
  {
    std::cout << "DONE TESTING AuthServer..." << std::endl;
  }

  virtual void SetUp() override
  {
    authServer = new AuthServer();
  }

  virtual void TearDown() override
  {
    delete authServer;
  }

  AuthServer *authServer;
};

TEST_F(AuthServerTest, isListening)
{
  authServer->listen();
  EXPECT_EQ(authServer->isListening(), true);
}

TEST_F(AuthServerTest, checkPort)
{
  authServer->listen();
  EXPECT_EQ(authServer->serverPort(), 8888);
}

TEST_F(AuthServerTest, checkCodeReceived)
{
  using namespace config;
  authServer->listen();
  const QString scopeStr = SCOPES.join("%20") + "%20";
  const QString url = AUTH_BASE_RUL + QString("?client_id=%1&response_type=code&redirect_uri=%2&scope=%3")
    .arg(CLIENT_ID)
    .arg(REDIRECT_URL)
    .arg(scopeStr)
  ;
  // Open the Auth PAGE in the default browser
  #ifdef WINDOWS
    ShellExecuteA(0, 0, url.toStdString().c_str(), 0, 0, SW_SHOW);
  #else
    qDebug() << "Please open the following URL in your browser: " << url;
  #endif

  QSignalSpy spy(authServer, SIGNAL(codeReceived(QString)));
  spy.wait(10000);
  CODE_TEST = spy.at(0).at(0).toString();
  qDebug() << CODE_TEST;
  EXPECT_EQ(spy.count(), 1);
}
