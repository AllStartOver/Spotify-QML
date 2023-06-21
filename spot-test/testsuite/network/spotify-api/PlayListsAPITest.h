#pragma once

#include <QObject>
#include <QSignalSpy>
#include <QDebug>
#include <gtest/gtest.h>
#include "network/spotify-api/PlayListsAPI.h"

#include "setting/account.h"

using namespace libspot::network::API;

class PlayListsAPITest : public testing::Test {

protected:

  static void SetupTestCase()
  {
    qDebug() << "TESTING PlayListsAPI...";
  }

  static void TearDownTestCase()
  {
    qDebug() << "DONE TESTING PlayListsAPI...";
  }

  virtual void SetUp() override
  {
    QString rootPath = QCoreApplication::applicationDirPath();
    account = new Account(rootPath);
    account->readFromFile();
    playListsAPI = new PlayListsAPI(nullptr, account->access_token);
  }

  virtual void TearDown() override
  {
    delete playListsAPI;
    delete account;
  }

  PlayListsAPI *playListsAPI;
  Account *account;
};

TEST_F(PlayListsAPITest, tempCheck)
{
  playListsAPI->getCurrentUserPlaylists();
  QSignalSpy spy(playListsAPI, &PlayListsAPI::signalMock);
  spy.wait(10000);
}