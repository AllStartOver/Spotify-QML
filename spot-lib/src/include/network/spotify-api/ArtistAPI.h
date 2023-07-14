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
  Q_PROPERTY(QQmlListProperty<ArtistPage> artistPages READ artistPages CONSTANT)
public: 
  explicit ArtistAPI(QObject *parent, QString &access_token);
  ~ArtistAPI() override;

  Q_INVOKABLE void requestUserFollowedArtists();
  Q_INVOKABLE void requestArtistByID(const QString& id);
  Q_INVOKABLE void requestArtistTopTracks(const QString& id);
  Q_INVOKABLE void requestArtistAlbums(const QString& id);
  Q_INVOKABLE void requestArtistRelatedArtists(const QString& id);
  Q_INVOKABLE ArtistPage* getCurrentArtistPage();
  QQmlListProperty<ArtistPage> artistPages();

signals:
  void signalRequestUserFollowedArtistsFinished();
  void signalRequestArtistByIDFinished();

private: 
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}}