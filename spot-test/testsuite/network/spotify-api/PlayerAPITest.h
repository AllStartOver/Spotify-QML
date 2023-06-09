#pragma once

#include <QObject>
#include <QSignalSpy>
#include <QDebug>
#include <gtest/gtest.h>
#include "network/spotify-api/PlayerAPI.h"
#include "setting/account.h"

using namespace libspot::network::API;
using namespace libspot::setting;

class PlayerAPITest : public testing::Test {

protected:

  static void SetupTestCase()
  {
    qDebug() << "TESTING PlayerAPI...";
  }

  static void TearDownTestCase()
  {
    qDebug() << "DONE TESTING PlayerAPI...";
  }

  virtual void SetUp() override
  {
    QString rootPath = QCoreApplication::applicationDirPath();
    account = new Account(rootPath);
    account->readFromFile();
    playerAPI = new PlayerAPI(nullptr, account->access_token);
  }

  virtual void TearDown() override
  {
    delete playerAPI;
    delete account;
  }

  PlayerAPI *playerAPI;
  Account *account;
};

TEST_F(PlayerAPITest, checkGetPlayerState)
{
}

TEST_F(PlayerAPITest, checkPausePlayback)
{
}