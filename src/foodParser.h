#ifndef FOODPARSER_H
#define FOODPARSER_H

#include <QString>
#include <QList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <httpEngine.h>
#include <kitchen.h>
#include <helperFunctions.h>
#include <QVector>
#include <QTextCodec>
#include <QNetworkReply>
#include <QDebug>
#include <restaurantmodel.h>
#include <QDate>

class foodParser : public QObject
{
    Q_OBJECT
public:
    foodParser(QObject *parent = 0);
    ~foodParser();

    Kitchen *getKitchenByName(QString kitchenName);
    void parseKitchens();
    void parseKitchenFood(QString kitchenName, QString lang);
    QList<QString> getKitchenNames();
    RestaurantModel *getModelByDate(QDate date);
    void addNewModel(QDate date);
    void clearModels();
    void deleteModel(QDate date);
    void parseKitchenOpeningHours(QString kitchenName);
    void getOpeningHours();

signals:
    void initData();
    void foodReady(const QList<QString> foods);

public slots:
    void parseInitData(const QByteArray &data);
    void parseFoodData(const QByteArray &data);
    void parseInfoData(const QByteArray &data, const QString kitchenName);
    void error(const QNetworkReply::NetworkError &error);

private:
    HTTPEngine *httpEngine_;
    QVector<Kitchen*> kitchens_;
    QMap<QDate, RestaurantModel*> models_;
    void addKitchens();
    QDate parseDate(QJsonDocument document);
};

#endif // FOODPARSER_H
