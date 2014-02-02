#ifndef SETTINGS_H
#define SETTINGS_H
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>
#include <QSettings>
#include <QString>
#include <QList>
#include <QStringList>
#include <QVariantList>

class SettingsManager
{
public:
    SettingsManager();
    ~SettingsManager();
    bool saveSettings(QList<QString> settings);
    QList<QString> loadSettings();

private:
    QSettings *settings_;
};

#endif // SETTINGS_H
