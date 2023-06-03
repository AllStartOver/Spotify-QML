#include <QGuiApplication>
#include <QCoreApplication>
#include <gtest/gtest.h>
// #include "testsuite/network/AuthServer.h"
// #include "testsuite/network/HttpAuthClient.h"
// #include "testsuite/controllers/AuthControllerTest.h"
#include "testsuite/setting/AccountTest.h"

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  QCoreApplication app(argc, argv);
  QString rootPath = QCoreApplication::applicationDirPath();

  qDebug() << rootPath;

  return RUN_ALL_TESTS();
}
