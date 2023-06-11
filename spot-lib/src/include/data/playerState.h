#pragma once 

#include <QObject>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>
#include <QQmlListProperty>
#include <QScopedPointer>
#include "data/artist.h"

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
  Q_PROPERTY(QString trackName READ trackName CONSTANT)

  Q_PROPERTY(QQmlListProperty<Artist> artists READ artists)
public:
  PlayerState();
  ~PlayerState();

  void updateBasicStates(QJsonObject json);
  void updateFullStates(QJsonObject json);

  // Q_READ @@@@@@@@@@@@@@@@@@@@@@@@
  QString& currentDeviceId() const;
  QString& curentDeviceName() const;

  int volumePercent() const;
  int progressMs() const;
  int durationMs() const;

  bool isPlaying() const;
  bool isShuffling() const;
  QString loopMode() const;

  QString trackName() const;
  QQmlListProperty<Artist> artists();

signals:
  void signalPlayerStateUpdated();
  void signalPlayerStateRemainsSame(bool forceTrackUpdate);
  void signalRequestImage(QString url);
  void signalRequestImageFinished(QString imgPath);

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};
}}