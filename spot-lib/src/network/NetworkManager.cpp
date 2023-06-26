#include "network/NetworkManager.h"

namespace libspot {
namespace network {

NetworkManager& NetworkManager::instance()
{
  static NetworkManager instance;
  return instance;
}

QNetworkAccessManager* NetworkManager::getNetworkManager()
{
  return &m_networkManager;
}

NetworkManager::NetworkManager() {}

NetworkManager::~NetworkManager() {}

}}