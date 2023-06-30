#pragma once

#include "network/spotify-api/BaseAPI.h"


using namespace libspot::data;

namespace libspot {
namespace network {
namespace API {

class AlbumAPI : public BaseAPI
{
  Q_OBJECT
public:
  explicit AlbumAPI(QObject *parent, QString &access_token);
  ~AlbumAPI() override;
};

}}}