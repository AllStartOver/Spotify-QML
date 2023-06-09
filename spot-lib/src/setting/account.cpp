#include "setting/account.h"

namespace libspot {
namespace setting {

Account::Account(QString rootPath)
{
  file_path = rootPath + "/setting" + "/account.json";
}

Account::~Account() {}

QJsonObject Account::toJson() const
{
  QJsonObject json;
  json["access_token"] = access_token;
  json["refresh_token"] = refresh_token;
  json["client_id"] = client_id;
  json["client_secret"] = client_secret;
  return json;
}

bool Account::readFromFile()
{
  if (file_path.isEmpty())
  {
    qDebug() << "Account::readFromFile: filePath is empty";
    return false;
  }
  QFile file(file_path);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QString jsonString = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject json = jsonDoc.object();
    client_id = json["client_id"].toString();
    client_secret = json["client_secret"].toString();
    access_token = json["access_token"].toString();
    refresh_token = json["refresh_token"].toString();
    file.close();
  }
  return true;
}

bool Account::localFileExists()
{
  if (file_path.isEmpty())
  {
    qDebug() << "Account::localFileExists: path is empty";
    return false;
  }
  QFile file(file_path);
  if (file.exists())
  {
    return true;
  }
  return false;
}

}}