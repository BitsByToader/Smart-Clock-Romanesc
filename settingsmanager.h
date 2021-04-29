#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QtSql>

class SettingsManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(int snoozeTime READ snoozeTime WRITE setSnoozeTime NOTIFY snoozeTimeChanged)
    Q_PROPERTY(QString alarmRingtone READ alarmRingtone WRITE setAlarmRingtone NOTIFY alarmRingtoneChanged)

public:
    explicit SettingsManager(QObject *parent = nullptr);

    int snoozeTime() {
        return getSetting("snooze").toInt();
    }

    QString alarmRingtone() {
        return getSetting("alarmSound");
    }

public slots:
    void setSnoozeTime(int snoozeTime) {
        setSetting("snooze", QString::number(snoozeTime));
        emit snoozeTimeChanged(snoozeTime);
    }

    void setAlarmRingtone(QString alarmRingtone) {
        setSetting("alarmSound", alarmRingtone);
        emit alarmRingtoneChanged(alarmRingtone);
    }

signals:
    void snoozeTimeChanged(int snoozeTime);
    void alarmRingtoneChanged(QString alarmRingtone);

private:
    void setSetting(QString key, QString value);
    QString getSetting(QString key);
};

#endif // SETTINGSMANAGER_H
