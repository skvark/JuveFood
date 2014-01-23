#include "foodAPI.h"

foodAPI::foodAPI(QObject *parent):
    QObject(parent)
{
    parser_ = new foodParser();
    settingsManager_ = new SettingsManager();
    QObject::connect(parser_, SIGNAL(initData()), this, SLOT(kitchensReady()));
    QObject::connect(parser_, SIGNAL(foodReady(const QList<QString>)), this, SLOT(populateFoodList(const QList<QString>)));
}

void foodAPI::update() {
    food_.clear();
    getFoodBySettings();
}

void foodAPI::getFoodBySettings()
{
    QString lang;
    QList<QString> settings = loadSettings();

    if (settings.length() != 0) {
        if (settings[settings.length() - 1] != NULL) {
            lang = settings[settings.length() - 1];
        } else {
            lang = QString("Finnish");
        }
    } else {
            lang = QString("Finnish");
    }

    foreach(QString name, settings) {
        parser_->parseKitchenFood(name, lang);
    }
}

// This slots is called automatically after the kitchens are initialized
// so that the UI updates
void foodAPI::kitchensReady()
{
    getFoodBySettings();
}

void foodAPI::populateFoodList(const QList<QString> &foods)
{
    food_.append(foods);
    emit dataReady(foods);
    food_.clear();
}

QList<QString> foodAPI::getFoods()
{
    return food_;
}

QList<QString> foodAPI::getUserKitchens()
{
    QList<QString> user;
    return user;
}

QList<QString> foodAPI::getKitchenNameList()
{
    return parser_->getKitchenNames();
}

void foodAPI::saveSettings(QList<QString> settings)
{
    settingsManager_->saveSettings(settings);
    getFoodBySettings();
}

QList<QString> foodAPI::loadSettings()
{
    return settingsManager_->loadSettings();
}
