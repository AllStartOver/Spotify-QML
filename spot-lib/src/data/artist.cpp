#include "data/artist.h"

using namespace libspot::network;
namespace libspot {
namespace data {

class Artist::Implementation 
{
public:
  Implementation(Artist* _parent, QJsonObject json)
    : parent(_parent)
  {
    id = json["id"].toString();
    name = json["name"].toString();

    // Image 
    if(json["images"].toArray().size() == 0) {
      return;
    }
    else {
      QJsonArray images = json["images"].toArray();
      imgUrl = images[0].toObject()["url"].toString();
    }
  }
  QNetworkAccessManager* manager = NetworkManager::instance().getNetworkManager();
  Artist *parent;
  QString id;
  QString name;
  QString imgUrl;
  QString uri;
  QString imgFileName;

  void requestArtistImage()
  {
    QString fileName = "cache_imgs/" + imgUrl.split("/").last() + ".jpg";
    imgFileName = fileName;
    if(QFile::exists(fileName)) {
      emit parent->signalRequestArtistImageFinished();
      return;
    }
    QNetworkRequest request(imgUrl);
    QNetworkReply* reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
      onRequestArtistImage(reply);
    });
  }

  void onRequestArtistImage(QNetworkReply* reply)
  {
    if(reply->error() != QNetworkReply::NoError) {
      qDebug() << "Artist::onRequestArtistImage: " << reply->errorString();
      return;
    }
    QFile file(imgFileName);
    if(file.open(QIODevice::WriteOnly)) {
      file.write(reply->readAll());
      file.close();
    }
    emit parent->signalRequestArtistImageFinished();
  }
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

Artist::Artist(QObject* parent, QJsonObject json)
  : QObject(parent)
{
  impl.reset(new Implementation(this, json));
}

Artist::~Artist() {}

// MEMBER FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@

void Artist::requestArtistImage()
{
  return impl->requestArtistImage();
}

// Q_READ @@@@@@@@@@@@@@@@@@@@@@@@

const QString& Artist::id() const
{
  return impl->id;
}

const QString& Artist::name() const
{
  return impl->name;
}

const QString& Artist::imgUrl() const
{
  return impl->imgUrl;
}

const QString& Artist::uri() const
{
  return impl->uri;
}

QString& Artist::imgFileName()
{
  return impl->imgFileName;
}

}}