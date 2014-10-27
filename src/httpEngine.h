#ifndef HTTPENGINE_H
#define HTTPENGINE_H

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QHash>
#include <QPair>

class HTTPEngine : public QObject
{
    Q_OBJECT
public:
    HTTPEngine(QObject *parent = 0);
    ~HTTPEngine();

    enum GetMethod
    {
        kitchens,
        kitchendata,
        kitcheninfo
    };

    GetMethod methods;

    void getKitchens();
    void getOneDayFoods(QList< QPair<QString, QString> >& queryItems);
    void getKitchenInfo(QList< QPair<QString, QString> >& queryItems, QString kitchen);

private:
    void parseOneDayFoodsRequest(QNetworkReply*);
    void parseKitchensDataRequest(QNetworkReply*);
    void parseKitchensInfoRequest(QNetworkReply*, QString kitchen);

signals:
    void oneDayfoodDataReady(const QByteArray &food);
    void kitchenData(const QByteArray &food);
    void kitchenInfo(const QByteArray &info, const QString kitchen);
    void networkError(QNetworkReply::NetworkError error);

public slots:
    void finished(QNetworkReply *reply);

private:
    QNetworkAccessManager nam_;
    QHash<QNetworkReply*, QPair<GetMethod, QString> > hash_;

};

#endif // HTTPENGINE_H
