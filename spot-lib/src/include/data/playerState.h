#pragma once 

#include <QObject>
#include <QJsonObject>
#include <QScopedPointer>

namespace libspot {
namespace data {

class PlayerState : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int progressMs READ progressMs)
  Q_PROPERTY(int durationMs READ durationMs)
  Q_PROPERTY(bool isPlaying READ isPlaying)
  Q_PROPERTY(bool isShuffling READ isShuffling)
  Q_PROPERTY(QString loopMode READ loopMode)
public:
  PlayerState();
  ~PlayerState();

  void updateBasicStates(QJsonObject json);
  void updateFullStates(QJsonObject json);

  // Q_READ
  QString& currentDeviceId() const;
  QString& curentDeviceName() const;

  int volumePercent() const;
  int progressMs() const;
  int durationMs() const;

  bool isPlaying() const;
  bool isShuffling() const;
  QString loopMode() const;

signals:
  void signalPlayerStateUpdated();
  void signalPlayerStateRemainsSame(bool forceTrackUpdate);

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};
}}