#pragma once

#include <QObject>
#include <QSignalSpy>
#include <QDebug>
#include <gtest/gtest.h>
#include "setting/account.h"

using namespace libspot::setting;

class AccountTest : public testing::Test {

protected:

  static void SetupTestCase()
  {
    qDebug() << "TESTING Account...";
  }

  static void TearDownTestCase()
  {
    qDebug() << "DONE TESTING Account...";
  }

  virtual void SetUp() override
  {
    QString rootPath = QCoreApplication::applicationDirPath();
    account = new Account(rootPath);
  }

  virtual void TearDown() override
  {
    delete account;
  }

  Account *account;
};

TEST_F(AccountTest, checkLocalFileNotExist)
{
  EXPECT_FALSE(account->localFileExists());
}

TEST_F(AccountTest, checkMemberVariableInitialization)
{
  EXPECT_EQ(account->client_id, "");
  EXPECT_EQ(account->client_secret, "");
  EXPECT_EQ(account->access_token, "");
  EXPECT_EQ(account->refresh_token, "");

  account->client_id = "client_id";
  account->client_secret = "client_secret";

  EXPECT_EQ(account->client_id, "client_id");
  EXPECT_EQ(account->client_secret, "client_secret");
}


TEST_F(AccountTest, checkSavetoFile)
{
  account->client_id = "client_id";
  account->client_secret = "client_secret";
  account->access_token = "access_token";
  account->refresh_token = "refresh_token";

  account->saveToFile();
}

TEST_F(AccountTest, checkReadFromFile)
{
  account->readFromFile();

  EXPECT_EQ(account->client_id, "client_id");
  EXPECT_EQ(account->client_secret, "client_secret");
  EXPECT_EQ(account->access_token, "access_token");
  EXPECT_EQ(account->refresh_token, "refresh_token");
}

TEST_F(AccountTest, checkLocalFileExist)
{
  EXPECT_TRUE(account->localFileExists());
}





