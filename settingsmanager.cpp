#include "settingsmanager.h"

SettingsManager::SettingsManager(QObject *parent) : QObject(parent) {
}

void SettingsManager::setSetting(QString key, QString value) {
    QSqlQuery query;

    query.prepare("UPDATE settings SET value = :val WHERE key = :key");
    query.bindValue(":key", key);
    query.bindValue(":val", value);

    query.exec();
}

QString SettingsManager::getSetting(QString key) {
    QSqlQuery query;

    query.prepare("SELECT key, value FROM settings WHERE key = :key");
    query.bindValue(":key", key);
    query.exec();
    query.first();

    return query.value(1).toString();
}
