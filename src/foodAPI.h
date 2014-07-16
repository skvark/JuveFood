#ifndef GETFOODDATA_H
#define GETFOODDATA_H

#include <QString>
#include <QList>
#include <foodParser.h>
#include <settings.h>
#include <restaurantmodel.h>
#include <QMap>
#include <QDebug>
#include <QDate>

/* Interface for UI.
*/

class foodAPI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool settingsLoading READ settingsLoadingStatus NOTIFY settingsLoading)
    Q_PROPERTY(QVariant getModelByDate READ getModelByDate CONSTANT)

public:
    foodAPI(QObject *parent = 0);
    ~foodAPI();

    Q_INVOKABLE QList<QString> getUserKitchens();
    Q_INVOKABLE QList<QString> getKitchenNameList();
    Q_INVOKABLE void saveSettings(QList<QString> settings);
    Q_INVOKABLE bool settingsLoadingStatus();
    Q_INVOKABLE QList<QString> loadSettings();
    Q_INVOKABLE QVariant getModelByDate() const;
    Q_INVOKABLE void setModelByDate(QDate date);

    void getFoodBySettings();
    void orderFoodsByKitchenName();


signals:
    // This signal is sent always when food data is fetched and ready
    void dataReady(QList<QString> foods);
    void loading(bool loading);
    void settingsLoading(bool loading);
    void modelChanged();

public slots:
    void kitchensReady();
    void update();

private:
    foodParser* parser_;
    SettingsManager* settingsManager_;
    bool settingsLoading_;
    RestaurantModel* model_;

};

#endif // GETFOODDATA_H
