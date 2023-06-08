#include <QGuiApplication>
#include <QCoreApplication>
#include <gtest/gtest.h>
// #include "testsuite/network/AuthServer.h"
// #include "testsuite/network/HttpAuthClient.h"
#include "testsuite/controllers/AuthControllerTest.h"
// #include "testsuite/setting/AccountTest.h"
// #include "testsuite/network/spotify-api/PlayerAPITest.h"

#include "controllers/AuthController.h"

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  QCoreApplication app(argc, argv);

  return RUN_ALL_TESTS();
}
