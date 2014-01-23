#ifndef GETFOODDATA_H
#define GETFOODDATA_H

#include <QString>
#include <QList>
#include <foodParser.h>
#include <settings.h>

/* Interface for UI.
*/

class foodAPI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> foods READ getFoods NOTIFY dataReady)
public:
    foodAPI(QObject *parent = 0);

    void getFoodBySettings();
    QList<QString> getFoods();
    Q_INVOKABLE QList<QString> getUserKitchens();
    Q_INVOKABLE QList<QString> getKitchenNameList();
    Q_INVOKABLE void saveSettings(QList<QString> settings);
    Q_INVOKABLE QList<QString> loadSettings();

signals:
    // This signal is sent always when food data is fetched
    void dataReady(QList<QString> foods);

public slots:
    void populateFoodList(const QList<QString> &foods);
    void kitchensReady();
    void update();

private:
    foodParser* parser_;
    QList<QString> food_;
    SettingsManager* settingsManager_;
};

#endif // GETFOODDATA_H
