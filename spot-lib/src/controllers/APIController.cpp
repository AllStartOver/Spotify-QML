#include "controllers/APIController.h"

namespace libspot {
namespace controllers {

APIController* APIController::instance()
{
  static APIController instance;
  return &instance;
}

PlayerAPI* APIController::getPlayerAPI()
{
  return m_playerAPI;
}

PlayListsAPI* APIController::getPlayListsAPI()
{
  return m_playListsAPI;
}

APIController::APIController()
{
}

APIController::~APIController()
{
}

void APIController::init(QString& access_token)
{
  m_playerAPI = new PlayerAPI(instance(), access_token);
  m_playListsAPI = new PlayListsAPI(instance(), access_token);
  m_playListsAPI->getCurrentUserPlaylists();
}

}}