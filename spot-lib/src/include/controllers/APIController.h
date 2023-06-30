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
  static APIController* instance();
  void init(QString& access_token);

  // API GETER
  PlayerAPI* getPlayerAPI();
  PlayListsAPI* getPlayListsAPI();

private:
  APIController();
  ~APIController();
  PlayerAPI* m_playerAPI;
  PlayListsAPI* m_playListsAPI;
};
}}