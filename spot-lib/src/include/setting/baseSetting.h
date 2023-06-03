#pragma once

#include <QFile>
#include <Qdir>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>

namespace libspot {
namespace setting {

struct BaseSetting {

  BaseSetting();
  virtual ~BaseSetting() = 0;

  QJsonObject virtual toJson() const = 0;
  void virtual readFromFile(const QString& filePath) = 0;

  void saveToFile(const QString& filePath) const;
};

}}



