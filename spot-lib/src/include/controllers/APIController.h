#pragma once

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QScopedPointer>

namespace libspot {
namespace controller {

class APIController : public QNetworkAccessManager
{
  Q_OBJECT
public:
  APIController(QObject* parent = 0);
  ~APIController();

private:
  class Implementation;
  QScopedPointer<Implementation> impl;
};
}}