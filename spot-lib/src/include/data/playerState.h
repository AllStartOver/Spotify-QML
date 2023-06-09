#pragma once 

#include <QObject>
#include <QJsonObject>
#include <QScopedPointer>

namespace libspot {
namespace data {

class PlayerState : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int progressMs READ progressMs WRITE setProgressMs NOTIFY progressMsChanged)
  Q_PROPERTY(int durationMs READ durationMs NOTIFY durationMsChanged)
public:
  PlayerState();
  ~PlayerState();

  void feed_json(QJsonObject json);

  // Q_READ
  QString& currentDeviceId() const;
  QString& curentDeviceName() const;

  int volumePercent() const;
  int progressMs() const;
  int durationMs() const;

  bool isPlaying() const;
  bool isShuffling() const;
  // Q_WRITE
  void setProgressMs(int progressMs);

signals:
  void progressMsChanged(int progressMs);
  void durationMsChanged(int durationMs);

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};
}}