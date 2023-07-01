#pragma once

#include <QObject>

namespace libspot {
namespace controllers {

class ViewController : public QObject
{
  Q_OBJECT
public:
  ViewController(QObject* parent = nullptr) : QObject(parent) {}
  ~ViewController() {}

signals:
  void signalChangePlayListSource(QString source, QString id);
  void signalChangeAlbumSource(QString source, QString id);
};

}}