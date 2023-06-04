#pragma once
#include <QObject>
#include <QDebug>
#include <QScopedPointer>
namespace libspot {
namespace network {
namespace API {

class BaseAPI : public QObject
{
  Q_OBJECT
public:
  BaseAPI(){};
  virtual ~BaseAPI() {}

  virtual void get() = 0;
  virtual void post() = 0;
  virtual void put() = 0;
};

}}}