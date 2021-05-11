#include "alarm.h"

Alarm::Alarm(QObject *parent) : QObject(parent) {
}

Alarm::Alarm(QString alarmName, int alarmHour, int alarmMinutes, QString alarmDays, bool alarmActivated, QObject *parent) : QObject(parent) {
    this->setAlarmName(alarmName);
    this->setAlarmHour(alarmHour);
    this->setAlarmMinutes(alarmMinutes);
    this->setAlarmDays(alarmDays);
    this->setAlarmActivated(alarmActivated);
    this->setAlarmUUID(QUuid::createUuid().toString(QUuid::WithoutBraces));
}

void Alarm::setAlarmName(QString alarmName) {
    if (m_alarmName == alarmName)
        return;

    m_alarmName = alarmName;
    emit alarmNameChanged(m_alarmName);
}

void Alarm::setAlarmHour(int alarmHour) {
    if (m_alarmHour == alarmHour)
        return;

    m_alarmHour = alarmHour;
    emit alarmHourChanged(m_alarmHour);
}

void Alarm::setAlarmMinutes(int alarmMinutes) {
    if (m_alarmMinutes == alarmMinutes)
        return;

    m_alarmMinutes = alarmMinutes;
    emit alarmMinutesChanged(m_alarmMinutes);
}

void Alarm::setAlarmDays(QString alarmDays) {
    if (m_alarmDays == alarmDays)
        return;

    m_alarmDays = alarmDays;
    emit alarmDaysChanged(m_alarmDays);
}

void Alarm::setAlarmActivated(bool alarmActivated) {
    if (m_alarmActivated == alarmActivated)
        return;

    m_alarmActivated = alarmActivated;
    emit alarmActivatedChanged(m_alarmActivated);
}

void Alarm::setAlarmUUID(const QString &alarmUUID) {
    m_alarmUUID = alarmUUID;
}
