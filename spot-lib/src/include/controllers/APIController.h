#pragma once

#include <QObject>
#include <QScopedPointer>
#include "network/spotify-api/PlayListsAPI.h"
#include "network/spotify-api/PlayerAPI.h"

using namespace libspot::network::API;
namespace libspot {
namespace controllers {

class APIController : public QObject
{
  Q_OBJECT
public:
  explicit APIController(QObject *parent, QString &access_token);
  ~APIController();

  // API GETER
  PlayerAPI* getPlayerAPI();
  PlayListsAPI* getPlayListsAPI();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};
}}