#pragma once
#include <QObject>
#include <QSignalSpy>
#include <QDebug>
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "network/HttpClientAuth.h"
#include "NetworkConfig.h"


using namespace libspot::network;

class HttpClientAuthTest : public testing::Test {

protected:

  static void SetUpTestCase()
  {
    std::cout << "TESTING HttpClientAuth..." << std::endl;
  }

  static void TearDownTestCase()
  {
    std::cout << "DONE TESTING HttpClientAuth..." << std::endl;
  }

  virtual void SetUp() override
  {
    authClient = new HttpClientAuth();
  }

  virtual void TearDown() override
  {
    delete authClient;
  }
  HttpClientAuth *authClient;
};

TEST_F(HttpClientAuthTest, checkTokenExpired)
{
  using namespace config;
  authClient->post(CODE_EXPIRED, REDIRECT_URL, CLIENT_ID, CLIENT_SECRET);

  QSignalSpy spy(authClient, SIGNAL(tokenExpired()));
  spy.wait(10000);
  EXPECT_EQ(spy.count(), 1);
}

TEST_F(HttpClientAuthTest, checkTokenReceived)
{
  using namespace config;
  authClient->post(CODE_TEST, REDIRECT_URL, CLIENT_ID, CLIENT_SECRET);

  QSignalSpy spy(authClient, SIGNAL(tokenReceived(QString, QString)));
  spy.wait(10000);
  EXPECT_EQ(spy.count(), 1);
}
