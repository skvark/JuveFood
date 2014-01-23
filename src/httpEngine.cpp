#include "httpengine.h"

const QString baseUrl = "http://www.juvenes.fi/DesktopModules/Talents.LunchMenu/LunchMenuServices.asmx";

HTTPEngine::HTTPEngine(QObject *parent) :
    QObject(parent)
{
    QObject::connect(&nam_, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finished(QNetworkReply*)));

}

void HTTPEngine::get(QList<QPair<QString, QString> > &queryItems)
{
    QUrlQuery url;
    url.setQueryItems(queryItems);
    QUrl api_url(baseUrl + "/GetMenubyWeekday?" + url.toString());
    QNetworkRequest request(api_url);
    QNetworkReply *reply = nam_.get(request);
    hash_[reply] = kitchendata;
}

void HTTPEngine::getKitchens()
{
    QUrlQuery url(baseUrl + "/GetKitchens?format=json");
    QUrl api_url(url.toString());
    QNetworkRequest request(api_url);
    QNetworkReply *reply = nam_.get(request);
    hash_[reply] = kitchens;
}

void HTTPEngine::finished(QNetworkReply *reply)
{
    switch(hash_[reply])
    {
    case kitchendata:
        parseGetRequest(reply);
        break;
    case kitchens:
        parseInitDataRequest(reply);
        break;
    }
    hash_.remove(reply);
}

void HTTPEngine::parseGetRequest(QNetworkReply *finished)
{
    if ( finished->error() != QNetworkReply::NoError )
    {
        return;
    }
    QByteArray data = finished->readAll();
    emit foodDataReady(data);
    finished->deleteLater();
}

void HTTPEngine::parseInitDataRequest(QNetworkReply *finished)
{
    if ( finished->error() != QNetworkReply::NoError )
    {
        return;
    }
    QByteArray data = finished->readAll();
    emit initData(data);
    finished->deleteLater();
}

