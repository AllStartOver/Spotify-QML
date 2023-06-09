#pragma once

#include "setting/baseSetting.h"

namespace libspot {
namespace setting {

struct Account : public BaseSetting
{
  QString access_token;
  QString refresh_token;
  QString client_id;
  QString client_secret;

  Account(QString rootPath);
  ~Account() override;

  QJsonObject toJson() const override;
  bool readFromFile() override;
  bool localFileExists();
};


}}