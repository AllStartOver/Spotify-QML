#pragma once
#include <QNetworkAccessManager>

namespace libspot {
namespace network {

class NetworkManager
{
public:
  static NetworkManager& instance();
  QNetworkAccessManager* getNetworkManager();

private:
  NetworkManager();
  ~NetworkManager();
  NetworkManager(const NetworkManager&) = delete;
  NetworkManager& operator=(const NetworkManager&) = delete;

  QNetworkAccessManager m_networkManager;
};

}}