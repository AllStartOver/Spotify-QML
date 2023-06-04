#include "controllers/APIController.h"

namespace libspot {
namespace controller {

class APIController::Implementation
{
public:
  Implementation(APIController* parent)
    : parent(parent) 
  {
  }

  APIController* parent;
};

APIController::APIController(QObject* parent)
  : QNetworkAccessManager(parent)
{
  impl.reset(new Implementation(this));
}

APIController::~APIController()
{
}

}}