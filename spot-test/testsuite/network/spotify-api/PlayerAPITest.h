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
    playerAPI = new PlayerAPI(account->access_token);
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
  playerAPI->getPlayerState();
  QSignalSpy spy(playerAPI, SIGNAL(signalGetPlayerStateFinished()));
  spy.wait(5000);
  EXPECT_EQ(spy.count(), 1);

  qDebug() << playerAPI->getCurrentDeviceId();
  qDebug() << playerAPI->getCurrentDeviceName();
  qDebug() << playerAPI->getVolumePercent();
  qDebug() << playerAPI->getProgressMs();
  qDebug() << playerAPI->getIsPlaying();
  qDebug() << playerAPI->getIsShuffling();
}

TEST_F(PlayerAPITest, checkPausePlayback)
{
}