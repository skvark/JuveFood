#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>
#include <QString>
#include <QList>
#include <QStringList>

class SettingsManager
{
public:
    SettingsManager();
    void saveSettings(QList<QString> settings);
    QList<QString> loadSettings();

private:
    QSettings *settings_;
};

#endif // SETTINGS_H
