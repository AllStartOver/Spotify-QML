#pragma once

#include <QObject>
#include <QSignalSpy>
#include <QDebug>
#include <gtest/gtest.h>
#include "network/spotify-api/PlayerAPI.h"

using namespace libspot::network::API;

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
    QString code("BQAc3uEYpYg6TqPHjpdLRdQzhu5486SGKt3jRVt5MX-lYp6Db4ueb51_d7-jCOe2p_B7o2xNNipr79Aw8k2TM3McUKPgWW0J0z1LTEu8EcLk4dvXM6j0VD0Cd1lJWv0NSr9YnHqYOBQBkkurIq279YOgFjXXtJ6kZeN4n1WSB8pQQrdwwE94qCiEa8i_4LtkSNfBrMzfvkkQJfhOzAz8-KKxnaDtW5U_wC3KvcdhE79Jaa3F0s49ySxeUHiM-XmKLyDXdrdq44ZymPZSIBUBOesDS02_fYloT5oLTr59G05r-y1bjp0vwW8gHLlCsfEGVBAc-k5C0o4TQ9Lp");
    playerAPI = new PlayerAPI(code);
  }

  virtual void TearDown() override
  {
    delete playerAPI;
  }

  PlayerAPI *playerAPI;
};

TEST_F(PlayerAPITest, checkInit)
{

}

TEST_F(PlayerAPITest, checkPausePlayback)
{
  playerAPI->pausePlayback();
}