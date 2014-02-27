#include "foodAPI.h"

foodAPI::foodAPI(QObject *parent):
    QObject(parent)
{
    parser_ = new foodParser();
    settingsManager_ = new SettingsManager();
    loading_ = true;
    settingsLoading_ = true;
    QObject::connect(parser_, SIGNAL(initData()),
                     this, SLOT(kitchensReady()));
    QObject::connect(parser_, SIGNAL(foodReady(const QList<QString>)),
                     this, SLOT(populateFoodList(const QList<QString>)));
}

foodAPI::~foodAPI()
{
    delete parser_;
    delete settingsManager_;
    parser_ = 0;
    settingsManager_ = 0;
}

void foodAPI::update() {
    getFoodBySettings();
}

void foodAPI::getFoodBySettings()
{
    loading_ = true;
    tempFoods_.clear();
    food_.clear();
    QString lang;
    QList<QString> settings = loadSettings();
    int size = settings.length();

    if (size < 2) {
        loading_ = false;
    }

    if (size != 0) {
        if (settings[size - 1] != NULL) {
            lang = settings[size - 1];
        } else {
            lang = QString("Finnish");
        }
    } else {
            lang = QString("Finnish");
    }

    parsedAndReady_ = size - 1;
    foreach(QString name, settings) {
        parser_->parseKitchenFood(name, lang);
    }
    emit loading(loading_);
}

// This slots is called automatically after the kitchens are initialized
// so that the UI updates
void foodAPI::kitchensReady()
{
    settingsLoading_ = false;
    emit settingsLoading(settingsLoading_);
    getFoodBySettings();
}

void foodAPI::populateFoodList(const QList<QString> &foods)
{
    // QMap orders stuff by key
    if (foods.empty()) {

    } else {
        tempFoods_.insert(foods[0], foods);
    }
    // Async reply counter
    --parsedAndReady_;
    // if everything parsed, we are ready to push data to UI
    if(parsedAndReady_ == 0) {
        loading_ = false;
        orderFoodsByKitchenName();
        emit dataReady(food_);
        emit loading(loading_);
    }
}

QList<QString> foodAPI::getFoods()
{
    return food_;
}

bool foodAPI::loadingStatus()
{
    return loading_;
}

bool foodAPI::settingsLoadingStatus()
{
    return settingsLoading_;
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
    if(settingsManager_->saveSettings(settings)) {
        getFoodBySettings();
    }
}

QList<QString> foodAPI::loadSettings()
{
    return settingsManager_->loadSettings();
}

void foodAPI::orderFoodsByKitchenName()
{
    QMapIterator<QString, QList<QString> > i(tempFoods_);
    while (i.hasNext()) {
        i.next();
        food_.append(i.value());
    }
}
