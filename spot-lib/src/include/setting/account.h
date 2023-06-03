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

  Account();
  ~Account() override;

  QJsonObject toJson() const override;
  void readFromFile(const QString& filePath) override;
};


}}