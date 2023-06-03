#include "setting/account.h"

namespace libspot {
namespace setting {

Account::Account() {}

QJsonObject Account::toJson() const
{
  QJsonObject json;
  json["access_token"] = access_token;
  json["refresh_token"] = refresh_token;
  return json;
}
}}