#include "httpengine.h"
#include <QDebug>

const QString baseUrl = "http://www.juvenes.fi/DesktopModules/Talents.LunchMenu/LunchMenuServices.asmx";

HTTPEngine::HTTPEngine(QObject *parent) :
    QObject(parent)
{
    QObject::connect(&nam_, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finished(QNetworkReply*)));

}

void HTTPEngine::getOneDayFoods(QList<QPair<QString, QString> > &queryItems)
{
    QUrlQuery url;
    url.setQueryItems(queryItems);
    QUrl api_url(baseUrl + "/GetMenubyWeekday?" + url.toString());
    QNetworkRequest request(api_url);
    QNetworkReply *reply = nam_.get(request);
    hash_[reply] = QPair<GetMethod, QString>(kitchendata, "");
}

void HTTPEngine::getKitchenInfo(QList<QPair<QString, QString> > &queryItems, QString kitchen)
{
    QUrlQuery url;
    url.setQueryItems(queryItems);
    QUrl api_url(baseUrl + "/GetKitchenInfo?" + url.toString());
    QNetworkRequest request(api_url);
    QNetworkReply *reply = nam_.get(request);
    hash_[reply] = QPair<GetMethod, QString>(kitcheninfo, kitchen);
}

void HTTPEngine::getKitchens()
{
    QUrlQuery url(baseUrl + "/GetKitchens?format=json");
    QUrl api_url(url.toString());
    QNetworkRequest request(api_url);
    QNetworkReply *reply = nam_.get(request);
    hash_[reply] = QPair<GetMethod, QString>(kitchens, "");
}

void HTTPEngine::finished(QNetworkReply *reply)
{
    switch(hash_[reply].first)
    {
    case kitchendata:
        parseOneDayFoodsRequest(reply);
        break;
    case kitchens:
        parseKitchensDataRequest(reply);
        break;
    case kitcheninfo:
        parseKitchensInfoRequest(reply, hash_[reply].second);
        break;
    }
    hash_.remove(reply);
}

void HTTPEngine::parseOneDayFoodsRequest(QNetworkReply *finished)
{
    if (finished->error() != QNetworkReply::NoError)
    {
        emit networkError(finished->error());
    }
    QByteArray data = finished->readAll();
    emit oneDayfoodDataReady(data);
    finished->deleteLater();
}

void HTTPEngine::parseKitchensDataRequest(QNetworkReply *finished)
{
    if (finished->error() != QNetworkReply::NoError)
    {
        return;
    }
    QByteArray data = finished->readAll();
    emit kitchenData(data);
    finished->deleteLater();
}

void HTTPEngine::parseKitchensInfoRequest(QNetworkReply *finished, QString kitchen)
{
    if (finished->error() != QNetworkReply::NoError)
    {
        return;
    }
    QByteArray data = finished->readAll();
    emit kitchenInfo(data, kitchen);
    finished->deleteLater();
}

