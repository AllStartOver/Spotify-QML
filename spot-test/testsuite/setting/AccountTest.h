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
    account = new Account();
  }

  virtual void TearDown() override
  {
    delete account;
  }

  Account *account;
};

TEST_F(AccountTest, checkMemberVariableInitialization)
{
  EXPECT_EQ(account->client_id, "");
}

