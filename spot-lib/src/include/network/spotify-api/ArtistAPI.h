#pragma once

#include "network/spotify-api/BaseAPI.h"
#include "data/artistPage.h"

using namespace libspot::data;

namespace libspot {
namespace network {
namespace API {

class ArtistAPI : public BaseAPI
{
  Q_OBJECT 
public: 
  explicit ArtistAPI(QObject *parent, QString &access_token);
  ~ArtistAPI() override;

  void requestUserFollowedArtists();

  QQmlListProperty<ArtistPage> artistPages();

signals:
  void signalRequestArtistByIDFinished();

private: 
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}}