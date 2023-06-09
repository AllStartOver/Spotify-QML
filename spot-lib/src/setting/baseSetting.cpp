#include <setting/baseSetting.h>

namespace libspot {
namespace setting {

BaseSetting::BaseSetting() {}

BaseSetting::~BaseSetting() {}

void BaseSetting::saveToFile() const
{
  QFile file(file_path);

  // create the directory if it doesn't exist
  QDir dir = QFileInfo(file_path).absoluteDir();
  if (!dir.exists())
  {
    dir.mkpath(".");
  }

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