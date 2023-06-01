#include <QGuiApplication>
#include <QCoreApplication>
#include <gtest/gtest.h>
#include "testsuite/network/AuthServer.h"

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::Test::HasFailure();
  QCoreApplication app(argc, argv);
  RUN_ALL_TESTS();
}
