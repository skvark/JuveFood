#ifndef GETFOODDATA_H
#define GETFOODDATA_H

#include <QString>
#include <QList>
#include <foodParser.h>
#include <settings.h>
#include <QMap>

/* Interface for UI.
*/

class foodAPI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> foods READ getFoods NOTIFY dataReady)
    Q_PROPERTY(bool loading READ loadingStatus NOTIFY loading)
public:
    foodAPI(QObject *parent = 0);

    void getFoodBySettings();
    QList<QString> getFoods();
    bool loadingStatus();
    Q_INVOKABLE QList<QString> getUserKitchens();
    Q_INVOKABLE QList<QString> getKitchenNameList();
    Q_INVOKABLE void saveSettings(QList<QString> settings);
    Q_INVOKABLE QList<QString> loadSettings();
    void orderFoodsByKitchenName();

signals:
    // This signal is sent always when food data is fetched
    void dataReady(QList<QString> foods);
    void loading(bool loading);

public slots:
    void populateFoodList(const QList<QString> &foods);
    void kitchensReady();
    void update();

private:
    foodParser* parser_;
    QList<QString> food_;
    QMap<QString, QList<QString> > tempFoods_;
    SettingsManager* settingsManager_;
    // helper variable to know when parsing is finished
    bool loading_;
    int parsedAndReady_;
};

#endif // GETFOODDATA_H
