#include <QEventLoop>
#include <QSignalSpy>
#include <iostream>
#include <gtest/gtest.h>
#include "network/AuthServer.h"


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
    authServer->listen();
    authServer->openAuthUrl();  
  }

  virtual void TearDown() override
  {
    delete authServer;
  }

  AuthServer *authServer;
};

TEST_F(AuthServerTest, isListening)
{
  EXPECT_EQ(authServer->isListening(), true);
}

TEST_F(AuthServerTest, checkPort)
{
  EXPECT_EQ(authServer->serverPort(), 8888);
}

TEST_F(AuthServerTest, checkCode)
{
  QSignalSpy spy(authServer, SIGNAL(codeReceived(QString, QString, QString, QString)));
  ASSERT_TRUE(spy.wait(100000));
  ASSERT_EQ(1, spy.count());
  std::cout << authServer->getCode().toStdString() << std::endl;
}

TEST_F(AuthServerTest, checkToken)
{
  std::cout << authServer->getCode().toStdString() << std::endl;
}
