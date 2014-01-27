#include "settings.h"

SettingsManager::SettingsManager()
{
    settings_ = new QSettings("JuveFood", "juvefood.api");
    settings_->setIniCodec("UTF-8");
}

bool SettingsManager::saveSettings(QList<QString> data)
{
    settings_->remove(QString("settings"));
    settings_->beginWriteArray(QString("settings"), data.size());
    int size = data.length();
    for (int i=0; i < size; ++i) {
        settings_->setValue("kitchen_" + QString::number(i), data[i]);
    }
    settings_->endArray();
    return true;
}

QList<QString> SettingsManager::loadSettings()
{
    settings_->sync();
    QList<QString> kitchens;
    settings_->beginGroup("settings");
    const QStringList childKeys = settings_->childKeys();

    foreach(const QString &childKey, childKeys)
    {
        if(childKey != "size") {
            kitchens.append(settings_->value(childKey).toString());
        }
    }
    settings_->endGroup();
    return kitchens;
}
