#pragma once

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>

namespace libspot {
namespace setting {

struct BaseSetting {

  BaseSetting();
  QJsonObject virtual toJson() const = 0;
  virtual ~BaseSetting() = 0;

  void saveToFile(const QString& filePath) const;
};

}}



