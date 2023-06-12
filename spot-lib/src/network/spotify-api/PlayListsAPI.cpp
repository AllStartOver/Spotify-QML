#include "network/spotify-api/PlayListsAPI.h"

namespace libspot {
namespace network {
namespace API {

class PlayListsAPI::Implementation
{
public:
  Implementation(PlayListsAPI* _parent, QString &_access_token)
    : parent(_parent),
      access_token(_access_token)
  {
    manager = new QNetworkAccessManager(parent);
  }

  PlayListsAPI* parent;
  QNetworkAccessManager* manager;
  QString& access_token;
  QString baseURL = "https://api.spotify.com/v1";

  // MEMBER FUNCTIONS
  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  void getCurrentUserPlayLists()
  {
    QString endpoint = "me/playlists";
    QNetworkRequest request = parent->createBaseRequest(endpoint, access_token);
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, parent, [reply = reply, this]() { onGetCurrentUserPlayLists(reply); });
  }
  // SLOTS
  // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  void onGetCurrentUserPlayLists(QNetworkReply *reply)
  {
    if (!parent->log(reply, "GetCurrentUserPlayLists")) 
    {
      reply->deleteLater();
      return;
    }
    QByteArray data = reply->readAll();
    QJsonObject json = QJsonDocument::fromJson(data).object();
    reply->deleteLater();
  }
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PlayListsAPI::PlayListsAPI(QObject *parent, QString &access_token)
{
  impl.reset(new Implementation(this, access_token));
}

PlayListsAPI::~PlayListsAPI()
{
}

void PlayListsAPI::getCurrentUserPlaylists()
{
}


}}}