#pragma once

#include <QFile>
#include <Qdir>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace libspot {
namespace setting {

struct BaseSetting {

  BaseSetting();
  virtual ~BaseSetting() = 0;

  QJsonObject virtual toJson() const = 0;
  bool virtual readFromFile() = 0;

  void saveToFile() const;

  QString file_path;
};

}}



