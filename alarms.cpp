#include "alarms.h"

Alarms::Alarms(QObject *parent) : QObject(parent) {
    Alarm *alarm1 = new Alarm("alarma1", 6, 30, {"Lu", "Ma"}, true);
    Alarm *alarm2 = new Alarm("scoala", 8, 00, {"Lu", "Ma"}, false);
    Alarm *alarm3 = new Alarm("viata", 9, 45, {"Lu", "Ma", "Mi"}, true);

    m_list.append(alarm1);
    m_list.append(alarm2);
    m_list.append(alarm3);

    //TODO create the alarms list here from the database
}

void Alarms::setList(QList<Alarm *> list) {
    if (m_list == list)
        return;

    m_list = list;
    emit listChanged(m_list);
}

void Alarms::addAlarm(QString alarmName, int alarmHour, int alarmMinutes, QList<QString> alarmDays, bool alarmActivated) {
    Alarm *newAlarm = new Alarm(alarmName, alarmHour, alarmMinutes, alarmDays, alarmActivated);

    m_list.append(newAlarm);
    emit listChanged(m_list);

    //TODO: add the alarm to the database here.
}

void Alarms::updateAlarm(QString alarmUUID, QString alarmName, int alarmHour, int alarmMinutes, QList<QString> alarmDays) {
    for ( int i = 0; i < m_list.count(); i++ ) {
        if ( m_list[i]->alarmUUID() == alarmUUID ) {
            //Get the alarm that needs updating.
            Alarm *alarmToUpdate = m_list[i];

            //Check if all the values have the default values.
            //If they don't then update them.
            if ( alarmName != "default_alarm_name" ) {
                alarmToUpdate->setAlarmName(alarmName);
            }

            if ( alarmHour != -1 ) {
                alarmToUpdate->setAlarmHour(alarmHour);
            }

            if ( alarmMinutes != -1 ) {
                alarmToUpdate->setAlarmMinutes(alarmMinutes);
            }

            if ( alarmDays.isEmpty() ) {
                alarmToUpdate->setAlarmDays(alarmDays);
            }

            break;
        }
    }

    //TODO update the databsae here with all the new/old values.
}

void Alarms::deleteAlarm(QString alarmUUID) {
    for ( int i = 0; i < m_list.count(); i++ ) {
        if ( m_list[i]->alarmUUID() == alarmUUID ) {
            //Deallocate the alarm that is marked as deleted.
            delete m_list[i];

            //Remove the dangling pointer from the list.
            m_list.removeAt(i);

            //Notify the UI that the list changed.
            emit listChanged(m_list);
            break;
        }
    }

    //TODO: delete the alarm from the database
}
