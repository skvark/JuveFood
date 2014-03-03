#include "foodParser.h"

foodParser::foodParser(QObject *parent):
    QObject(parent)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    httpEngine_ = new HTTPEngine();

    QObject::connect(httpEngine_, SIGNAL(initData(const QByteArray&)),
                     this, SLOT(parseInitData(const QByteArray&)));

    QObject::connect(httpEngine_, SIGNAL(foodDataReady(const QByteArray&)),
                     this, SLOT(parseFoodData(const QByteArray&)));

    QObject::connect(httpEngine_, SIGNAL(networkError(const QNetworkReply::NetworkError&)),
                     this, SLOT(error(const QNetworkReply::NetworkError&)));

    parseKitchens();
}

foodParser::~foodParser()
{
    delete httpEngine_;
    httpEngine_ = 0;
    foreach(Kitchen* kitchen, kitchens_) {
        delete kitchen;
        kitchen = 0;
    }
}

void foodParser::parseKitchens()
{
    httpEngine_->getKitchens();
}

Kitchen *foodParser::getKitchenByName(QString kitchenName)
{
    foreach(Kitchen* kitchen, kitchens_) {
        if (kitchen->getKitchenName() == kitchenName) {
            return kitchen;
        }
    }
    return NULL;
}

// Gets all the foods from a kitchen
void foodParser::parseKitchenFood(QString kitchenName, QString lang)
{
    Kitchen *kitchen = getKitchenByName(kitchenName);
    if (kitchen == NULL) {
        return;
    }
    QList<QPair<QString, QString> >  params = kitchen->getByWeekdayQuery(lang);
    httpEngine_->get(params);
}

QList<QString> foodParser::getKitchenNames()
{
    QList<QString> kitchens;
    foreach (Kitchen* kitchen, kitchens_) {
        kitchens.append(kitchen->getKitchenName());
    }
    return kitchens;
}

/* This slot is called when app is started.
 * It inits Kitchen objects so that food info
 * can be fetched according to the user selected Kitchen(s)
 * Sends a signal which indicates that kitchens are ready.
 */
void foodParser::parseInitData(const QByteArray &data)
{
    QByteArray data2 = data;
    cleanJSON(data2);
    QJsonParseError err;

    QJsonDocument doc = QJsonDocument::fromJson(data2, &err);
    QJsonArray restaurants = doc.array();

    foreach (const QJsonValue &value, restaurants) {

        QJsonObject obj = value.toObject();
        QJsonArray menus = obj[QString("MenuTypes")].toArray();

        foreach (const QJsonValue &subKitchen, menus) {

            Kitchen* kitchen = NULL;
            QJsonObject kitchenInfo = subKitchen.toObject();

            QString name = kitchenInfo[QString("KitchenName")].toString().toUtf8() +
                   QString(" - ") +
                   kitchenInfo[QString("Name")].toString().toUtf8();
            QString shortName;

            nameCompactor(name, shortName);



            kitchen = new Kitchen(kitchenInfo[QString("KitchenId")].toDouble(),
                                  kitchenInfo[QString("KitchenInfoId")].toDouble(),
                                  kitchenInfo[QString("OpenInfoId")].toDouble(),
                                  kitchenInfo[QString("MenuTypeId")].toDouble(),
                                  name,
                                  shortName);
            kitchens_.push_back(kitchen);
            name.clear();
        }
    }
    emit initData();
}

/* This slot is called when food data is fetched.
 * Emits signal containing restaurants specific foods.
 */
void foodParser::parseFoodData(const QByteArray &data)
{
    QByteArray data2 = data;
    cleanJSON(data2);
    QJsonParseError err;
    QList<QString> foods;
    QList<QString> mainFoodNames;

    QJsonDocument doc = QJsonDocument::fromJson(data2, &err);

    if(doc.isEmpty()) {
        emit foodReady(foods);
    }

    QJsonObject restaurant = doc.object();
    QJsonArray mealoptions = restaurant["MealOptions"].toArray();

    QString name = restaurant["KitchenName"].toString() + QString(" - ") +
                   restaurant["MenuTypeName"].toString();

    QString shortName;

    nameCompactor(name, shortName);


    foods.append(shortName);

    foreach (const QJsonValue &value, mealoptions) {

        QString food = "";
        QJsonObject obj = value.toObject();

        // check for force majoure condition
        if (obj["ForceMajeure"].toString() != "") {
            food += QString("\u2022 ") + obj["ForceMajeure"].toString();
            foods.append(food);
            mainFoodNames.append(food);
            continue;
        }

        QJsonArray arr = obj["MenuItems"].toArray();
        unsigned int counter = 0;

        foreach (const QJsonValue &value2, arr) {
            QJsonObject obj = value2.toObject();
            if(counter > 0) {
                food += ", " + obj["Name"].toString();
            } else {
                food += QString("\u2022 ") + obj["Name"].toString();
                mainFoodNames.append(QString("\u2022 ") + obj["Name"].toString());
            }
            ++counter;
        }
        if (food.length() > 0) {
            foods.append(food);
        }
    }

    // save main food names
    if (getKitchenByName(name) != NULL) {
        getKitchenByName(name)->addTodaysFoods(mainFoodNames);
    }

    if (foods.length() > 2) {
        foods.append(QString(""));
        emit foodReady(foods);
    } else {
        QList<QString> empty;
        emit foodReady(empty);
    }
}

void foodParser::error(const QNetworkReply::NetworkError &)
{
    QList<QString> empty;
    emit foodReady(empty);
}



