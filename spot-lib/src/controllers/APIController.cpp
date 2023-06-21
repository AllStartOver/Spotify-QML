#include "controllers/APIController.h"

using namespace libspot::network::API;
namespace libspot {
namespace controllers {

class APIController::Implementation
{
public:
  Implementation(APIController* _parent, QString &access_token)
    : parent(_parent) 
  {
    playerAPI = new PlayerAPI(parent, access_token);
    playListsAPI = new PlayListsAPI(parent, access_token);
    playListsAPI->getCurrentUserPlaylists();
  }
  APIController *parent;
  PlayerAPI *playerAPI;
  PlayListsAPI *playListsAPI;
};

//#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

APIController::APIController(QObject *parent, QString &access_token)
  : QObject(parent)
{
  impl.reset(new Implementation(this, access_token));
}

APIController::~APIController()
{
}

//#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PlayerAPI* APIController::getPlayerAPI()
{
  return impl->playerAPI;
}

PlayListsAPI* APIController::getPlayListsAPI()
{
  return impl->playListsAPI;
}

}}