#include "data/baseData.h"

using namespace libspot::network;

namespace libspot {
namespace data {

class BaseData::Implementation 
{
public: 
  Implementation(BaseData* _parent, QJsonObject json)
    : parent(_parent)
  {
    id = json["id"].toString();
    name = json["name"].toString();
    uri = json["uri"].toString();
    if(json["images"].toArray().size() == 0) {
      return;
    }
    else {
      imgUrls = json["images"].toArray();
      //imgUrl = images[images.size()-1].toObject()["url"].toString();
    }
  }
  BaseData *parent;
  QNetworkAccessManager *manager = NetworkManager::instance().getNetworkManager();
  QString id;
  QString name;
  QString uri;
  QString imgFileName;
  QString averageCoverColor;
  QJsonArray imgUrls;

  // MEMBER FUNCS @@@@@@@@@@@@@@@@@@@@@j

  void requestImage(bool highRes) 
  {
    QString imgUrl = !highRes ? imgUrls[0].toObject()["url"].toString() : imgUrls[imgUrls.size()-1].toObject()["url"].toString();
    QString fileName = "cache_imgs/" + imgUrl.split("/").last() + ".jpg";
    imgFileName = fileName;
    if(QFile::exists(fileName)) {
      emit parent->signalRequestImageFinished();
      return;
    }
    QNetworkRequest request(imgUrl);
    QNetworkReply* reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
      onRequestImage(reply);
    });
  }

  void calculateAverageCoverColor() 
  {
    if (averageCoverColor != "") {
      return;
    }
    if (imgFileName.isEmpty()) {
      qDebug() << "Album::calculateAverageCoverColor: imgFileName is empty";
      return;
    }
    QImage img(imgFileName);
    if (img.isNull()) {
      qDebug() << "Album::calculateAverageCoverColor: img is null";
      return;
    }
    int r = 0, g = 0, b = 0;
    int count = 0;
    for (int x = 0; x < img.width(); x += 10) {
      for (int y = 0; y < img.height(); y += 10) {
        QColor color = img.pixelColor(x, y);
        r += color.red();
        g += color.green();
        b += color.blue();
        count++;
      }
    }
    r /= count;
    g /= count;
    b /= count;
    averageCoverColor = QColor(r, g, b).name();
  }

  // SLOTS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  void onRequestImage(QNetworkReply* reply) 
  {
    if(reply->error() != QNetworkReply::NoError) {
      qDebug() << "BaseData::onRequestImage: " << reply->errorString();
      return;
    }
    QFile file(imgFileName);
    if(file.open(QIODevice::WriteOnly)) {
      file.write(reply->readAll());
      file.close();
    }
    emit parent->signalRequestImageFinished();
  }
};

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

BaseData::BaseData(QObject* parent, QJsonObject json)
  : QObject(parent)
  , impl(new Implementation(this, json))
{
}

BaseData::~BaseData()
{
}

// Q_READ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

const QString& BaseData::id() const
{
  return impl->id;
}

const QString& BaseData::name() const
{
  return impl->name;
}

const QString& BaseData::uri() const
{
  return impl->uri;
}

const QString& BaseData::imgFileName() const
{
  return impl->imgFileName;
}

const QString& BaseData::averageCoverColor() const
{
  return impl->averageCoverColor;
}

// MEMBER FUNCS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void BaseData::requestImage(bool highRes)
{
  return impl->requestImage(highRes);
}

void BaseData::calculateAverageCoverColor()
{
  return impl->calculateAverageCoverColor();
}

}}