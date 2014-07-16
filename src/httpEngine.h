#ifndef HTTPENGINE_H
#define HTTPENGINE_H

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QHash>

class HTTPEngine : public QObject
{
    Q_OBJECT
public:
    HTTPEngine(QObject *parent = 0);
    enum GetMethod
    {
        kitchens,
        kitchendata
    };
    GetMethod methods;
    void getKitchens();
    void getOneDayFoods(QList< QPair<QString, QString> >& queryItems);
    void getKitchenInfo(QList< QPair<QString, QString> >& queryItems);

private:
    void parseOneDayFoodsRequest(QNetworkReply*);
    void parseKitchensDataRequest(QNetworkReply*);

signals:
    void oneDayfoodDataReady(const QByteArray &food);
    void kitchenData(const QByteArray &food);
    void networkError(QNetworkReply::NetworkError error);

public slots:
    void finished(QNetworkReply *reply);

private:
    QNetworkAccessManager nam_;
    QHash<QNetworkReply*, GetMethod> hash_;

};

#endif // HTTPENGINE_H
