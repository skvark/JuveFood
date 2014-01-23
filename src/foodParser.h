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

class foodParser : public QObject
{
    Q_OBJECT
public:
    foodParser(QObject *parent = 0);

    Kitchen *getKitchenByName(QString kitchenName);
    void parseKitchens();
    void parseKitchenFood(QString kitchenName, QString lang);
    QList<QString> getKitchenNames();

signals:
    void initData();
    void foodReady(const QList<QString> foods);

public slots:
    void parseInitData(const QByteArray &data);
    void parseFoodData(const QByteArray &data);

private:
    HTTPEngine *httpEngine_;
    QVector<Kitchen*> kitchens_;
    void addKitchens();
};

#endif // FOODPARSER_H
