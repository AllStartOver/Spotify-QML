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
    playerAPI = new PlayerAPI();
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