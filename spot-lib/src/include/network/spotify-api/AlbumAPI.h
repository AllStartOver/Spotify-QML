#pragma once

#include "network/spotify-api/BaseAPI.h"
#include "data/album.h"

using namespace libspot::data;

namespace libspot {
namespace network {
namespace API {

class AlbumAPI : public BaseAPI
{
  Q_PROPERTY(QString currentAlbumID READ currentAlbumID CONSTANT)
  Q_OBJECT
public:
  explicit AlbumAPI(QObject *parent, QString &access_token);
  ~AlbumAPI() override;

  Q_INVOKABLE void requestAlbumByID(const QString &id);
  Q_INVOKABLE Album* getAlbumByID(const QString &id);
  Q_INVOKABLE Album* getCurrentAlbum();

  QString& currentAlbumID() const;

signals:
  void signalRequestAlbumByIDFinished();
  void signalCurrentAlbumChanged();
  void signalAlbumRequestCoverFinished();
  void signalMock();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};

}}}
