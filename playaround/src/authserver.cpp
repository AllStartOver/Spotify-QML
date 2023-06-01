#include "authserver.h"

std::string joinStr(std::vector<std::string> &v, std::string delim)
{
    std::string s;
    for (auto &i : v)
    {
        s += i + delim;
    }
    return s;
}

AuthServer::AuthServer(QObject *parent) : QTcpServer(parent)
{
  QTcpServer::connect(this, &QTcpServer::newConnection, this, &AuthServer::onNewConnection);
}

AuthServer::~AuthServer()
{
}

auto AuthServer::listen() -> bool
{
  return QTcpServer::listen(QHostAddress::LocalHost, PORT);
}

auto AuthServer::redirectUrl() -> QString
{
  return QString("http://localhost:%1").arg(PORT);
}

void AuthServer::openUrl() const
{
  std::vector<std::string> scopes = {
    "playlist-read-collaborative",
		"playlist-read-private",
		"playlist-modify-private",
		"playlist-modify-public",
		"user-follow-read",
		"user-follow-modify",
		"user-library-modify",
		"user-library-read",
		"user-modify-playback-state",
		"user-read-currently-playing",
		"user-read-playback-state",
		"user-read-private",
		"user-read-recently-played",
		"streaming",
		"user-read-email",
		"user-top-read"
  };

  std::string scopeStr = joinStr(scopes, "%20");
  std::string _url = 
    fmt::format("https://accounts.spotify.com/authorize?client_id={0}&response_type=code&redirect_uri={1}&scope={2}", client_id.toStdString(), redirectUrl().toStdString(), scopeStr);
  QString url = QString::fromStdString(_url); 

  std::cout << url.toStdString() << std::endl;

  ShellExecute(0, 0, url.toStdWString().c_str(), 0, 0, SW_SHOW);
}


void AuthServer::onNewConnection()
{
	// Read
	auto *socket = nextPendingConnection();
	socket->waitForReadyRead();
	auto response = QString(socket->readAll());

	// Unrelated request, ignore
	if (!response.contains(QStringLiteral("?code=")))
	{
		socket->close();
		return;
	}

	// Do magic with code received
	// GET /?code=<code> HTTP...
	auto left = response.left(response.indexOf(QStringLiteral(" HTTP")));
	auto code = left.right(left.length() - left.indexOf(QStringLiteral("?code=")) - 6);

  std::cout << "code: " << std::endl;
  std::cout << code.toStdString() << std::endl;

  auto reponse = auth->get(code, redirectUrl(), client_id, client_secret);

  std::cout << reponse.toStdString() << std::endl;

  // 

	socket->flush();
	socket->waitForBytesWritten(writeTimeout);
	socket->close();

	close();
	emit success();
}