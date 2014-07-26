#include "foodParser.h"

foodParser::foodParser(QObject *parent):
    QObject(parent)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    httpEngine_ = new HTTPEngine();

    QObject::connect(httpEngine_, SIGNAL(kitchenData(const QByteArray&)),
                     this, SLOT(parseInitData(const QByteArray&)));

    QObject::connect(httpEngine_, SIGNAL(oneDayfoodDataReady(const QByteArray&)),
                     this, SLOT(parseFoodData(const QByteArray&)));

    QObject::connect(httpEngine_, SIGNAL(networkError(const QNetworkReply::NetworkError&)),
                     this, SLOT(error(const QNetworkReply::NetworkError&)));
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
    foreach(auto date, models_.keys()) {
        QList<QPair<QString, QString> >  params = kitchen->getByWeekdayQuery(lang, date);
        httpEngine_->getOneDayFoods(params);
    }
}

QList<QString> foodParser::getKitchenNames()
{
    QList<QString> kitchens;
    foreach (Kitchen* kitchen, kitchens_) {
        kitchens.append(kitchen->getKitchenName());
    }
    return kitchens;
}

RestaurantModel *foodParser::getModelByDate(QDate date)
{
    if(models_.find(date) != models_.end()) {
        return models_.value(date);
    } else {
        return nullptr;
    }
}

void foodParser::addNewModel(QDate date)
{
    RestaurantModel *model = new RestaurantModel();
    models_.insert(date, model);
}

void foodParser::clearModels()
{
    foreach(auto model, models_) {
        model->clear();
    }
}

void foodParser::deleteModel(QDate date)
{
    models_.value(date)->clear();
    delete models_.value(date);
    models_.erase(models_.find(date));
}

QDate foodParser::parseDate(QJsonDocument document) {

    QJsonObject restaurant = document.object();
    QJsonArray mealoptions = restaurant["MealOptions"].toArray();
    QDate date;

    foreach (auto value, mealoptions) {
        QJsonObject obj = value.toObject();
        if (obj["MenuDate"].toString() != "") {
            QString dirty = obj["MenuDate"].toString();
            QStringList list = dirty.split(QChar('.'));
            date.setDate(list[2].toInt(),
                          list[1].toInt(),
                          list[0].toInt());
            return date;
        }
    }
    return date;
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

            kitchens_.append(kitchen);
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

    QJsonDocument doc = QJsonDocument::fromJson(data2, &err);

    if(doc.isEmpty()) {
        return;
    }

    QDate date = parseDate(doc);

    if(models_.find(date) == models_.end()) {
        RestaurantModel* model = new RestaurantModel();
        models_.insert(date, model);
    }

    QJsonObject restaurant = doc.object();
    QJsonArray mealoptions = restaurant["MealOptions"].toArray();

    QString name = restaurant["KitchenName"].toString() + QString(" - ") +
                   restaurant["MenuTypeName"].toString();

    QString shortName;
    nameCompactor(name, shortName);

    foreach (auto value, mealoptions) {

        QString food = "";
        QJsonObject obj = value.toObject();

        // check for force majoure condition
        if (obj["ForceMajeure"].toString() != "") {
            food += QString("\u2022 ") + obj["ForceMajeure"].toString();
            foods.append(food);
            continue;
        }

        QJsonArray arr = obj["MenuItems"].toArray();
        unsigned int counter = 0;

        foreach (auto value2, arr) {
            QJsonObject obj = value2.toObject();
            if(counter > 0) {
                food += ", " + obj["Name"].toString();
            } else {
                food += QString("\u2022 ") + obj["Name"].toString();
            }
            ++counter;
        }
        if (food.length() > 0) {
            foods.append(food);
        }
    }

    RestaurantModel* model = models_.find(date).value();
    Restaurant* res = models_.find(date).value()->alreadyAdded(name);

    if(!res) {
        Restaurant* restaurant = new Restaurant(name, shortName, foods);
        model->addRestaurant(restaurant);
    } else {
        res->setFoods(foods);
    }
}

void foodParser::error(const QNetworkReply::NetworkError &)
{
    QList<QString> empty;
    emit foodReady(empty);
}



