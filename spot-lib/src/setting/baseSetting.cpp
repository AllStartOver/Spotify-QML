#include <setting/baseSetting.h>

namespace libspot {
namespace setting {

BaseSetting::BaseSetting() {}

BaseSetting::saveToFile(const QString &filepath) const
{
  QFile file(filepath);

  if (file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    QJsonObject json = toJson();
    QJsonDocument jsonDoc(json);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Indented);
    QTextStream out(&file);
    out << jsonString;
    file.close();
  }
}

}}