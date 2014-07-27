#include "foodAPI.h"

foodAPI::foodAPI(QObject *parent):
    QObject(parent)
{
    parser_ = new foodParser();
    settingsManager_ = new SettingsManager();
    settingsLoading_ = true;
    QObject::connect(parser_, SIGNAL(initData()),
                     this, SLOT(kitchensReady()));
}

foodAPI::~foodAPI()
{
    delete parser_;
    delete settingsManager_;
    parser_ = 0;
    settingsManager_ = 0;
}

void foodAPI::init() {
    parser_->parseKitchens();
}

void foodAPI::deleteModel(QDate date)
{
    parser_->deleteModel(date);
}

QString foodAPI::getOpeningHours(QString kitchenName)
{
    Kitchen* kitchen = parser_->getKitchenByName(kitchenName);
    if(kitchen) {
        return kitchen->getOpeningHours();
    }
    return QString("");
}

void foodAPI::update() {
    parser_->clearModels();
    getFoodBySettings();
}

// creates new model by date and initializes
// it with restaurants in the settings
void foodAPI::createNewModel(QDate date) {
    parser_->addNewModel(date);
}

void foodAPI::getFoodBySettings()
{
    QString lang;
    QList<QString> settings = loadSettings();
    int size = settings.length();

    if (size != 0) {
        if (settings[size - 1] != NULL) {
            lang = settings[size - 1];
        } else {
            lang = QString("Finnish");
        }
    } else {
            lang = QString("Finnish");
    }

    foreach(QString name, settings) {
        parser_->parseKitchenFood(name, lang);
    }
    parser_->getOpeningHours();
}

// This slots is called automatically after the kitchens are initialized
// so that the UI updates
void foodAPI::kitchensReady()
{
    settingsLoading_ = false;
    emit settingsLoading(settingsLoading_);
    getFoodBySettings();
}

QVariant foodAPI::getModelByDate(QDate date) const
{ 
    return QVariant::fromValue((QObject*) parser_->getModelByDate(date));
}

bool foodAPI::settingsLoadingStatus()
{
    return settingsLoading_;
}

QList<QString> foodAPI::getKitchenNameList()
{
    return parser_->getKitchenNames();
}

void foodAPI::saveSettings(QList<QString> settings)
{
    if(settingsManager_->saveSettings(settings)) {
        update();
    }
}

QList<QString> foodAPI::loadSettings()
{
    return settingsManager_->loadSettings();
}
