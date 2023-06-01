#include <iostream>
#include <QGuiApplication>
#include <fmt/core.h>
#include "src/authserver.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    std::vector<std::string> scopes = {
        "playlist-read-collaborative",
        "playlist-read-private",
        "playlist-modify-private",
    };

    AuthServer *auth = new AuthServer();
    auth->listen();
    std::cout << auth->isListening() << std::endl;
    auth->openUrl();
    
    return app.exec();
}