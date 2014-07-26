#include "foodAPI.h"

foodAPI::foodAPI(QObject *parent):
    QObject(parent)
{
    parser_ = new foodParser();
    settingsManager_ = new SettingsManager();
    settingsLoading_ = true;
    setModelByDate(QDate(2014, 7, 24));
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

void foodAPI::update() {
    getFoodBySettings();
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
        parser_->parseKitchenFood(name, lang, QDate(2014, 7, 24));
    }
}

// This slots is called automatically after the kitchens are initialized
// so that the UI updates
void foodAPI::kitchensReady()
{
    settingsLoading_ = false;
    emit settingsLoading(settingsLoading_);
    getFoodBySettings();
}

QVariant foodAPI::getModelByDate() const
{ 
    return QVariant::fromValue((QObject*) model_);
}

void foodAPI::setModelByDate(QDate date)
{
    model_ = parser_->getModelByDate(date);
    emit modelChanged();
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
