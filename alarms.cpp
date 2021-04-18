#include "alarms.h"

Alarms::Alarms(QObject *parent) : QObject(parent) {
    QSqlQuery query;

    //With the database connection already open, we can read the alarms from the database and put them in memory.
    query = QSqlQuery("SELECT alarmID, alarmName, alarmHour, alarmMinutes, alarmDays, alarmActivated FROM alarms;");

    while ( query.next() ) {
        Alarm *alarmToAdd = new Alarm();

        alarmToAdd->setAlarmUUID(query.value(0).toString());
        alarmToAdd->setAlarmName(query.value(1).toString());
        alarmToAdd->setAlarmHour(query.value(2).toInt());
        alarmToAdd->setAlarmMinutes(query.value(3).toInt());
        alarmToAdd->setAlarmDays(query.value(4).toString());
        alarmToAdd->setAlarmActivated(query.value(5).toInt());

        m_list.append(alarmToAdd);
        alarmsHashedByID.insert(alarmToAdd->alarmUUID(), alarmToAdd);
    }

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Alarms::checkForAlarms);
    ///TODO: FIX THIS ERROR REGARDING THREADS^^^
    timer->start(1000);
}

void Alarms::checkForAlarms() {
    qDebug()<<"Checking for pending alarms...";

    QDateTime currentDate = QDateTime::currentDateTime();

    QSqlQuery query("SELECT alarmHour, alarmName, alarmDays, alarmActivated, alarmID FROM alarms;");

    while ( query.next() ) {
        int hour = query.value(0).toInt();
        int minutes = query.value(1).toInt();
        QString days = query.value(2).toString();
        QStringList daysArray = days.split(" ");
        bool activated = query.value(3).toInt();
        QString alarmID = query.value(4).toString();

        if ( activated ) {
            if ( hour == currentDate.time().hour() && minutes == currentDate.time().minute() ) {
                if ( daysArray.isEmpty() ) {
                    //If the array is empty then the alarm shouldn't repeat so we disable it.
                    alarmsHashedByID[alarmID]->setAlarmActivated(false);

                    ///TODO: Ring the alarm here.
                    /// When ringing the alarm, also call a function to update the alarm headline.
                    qDebug()<<"Rang!";
                    break;
                } else if ( daysArray.contains( daysOfWeekList[currentDate.date().dayOfWeek()] ) ) {
                    //The array isn't empty and we are in the correct day to ring the alarm.
                    ///TODO: Ring the alarm here.
                    qDebug()<<"Rang!";
                    break;
                }

                //We aren't in the correct day, so we don't ring the alarm...
            }
        }
    }
}

void Alarms::setList(QList<Alarm *> list) {
    if (m_list == list)
        return;

    m_list = list;
    emit listChanged(m_list);
}

void Alarms::addAlarm(QString alarmName, int alarmHour, int alarmMinutes, QString alarmDays, bool alarmActivated) {
    Alarm *newAlarm = new Alarm(alarmName, alarmHour, alarmMinutes, alarmDays, alarmActivated);

    m_list.append(newAlarm);
    emit listChanged(m_list);

    QSqlQuery query;
    query.prepare("INSERT INTO alarms (alarmID, alarmName, alarmHour, alarmMinutes, alarmDays, alarmActivated) VALUES (:alarmUUID, :alarmName, :alarmHour, :alarmMinutes, :alarmDays, :alarmActivated);");
    query.bindValue(":alarmUUID", newAlarm->alarmUUID());
    query.bindValue(":alarmName", alarmName);
    query.bindValue(":alarmHour", alarmHour);
    query.bindValue(":alarmMinutes", alarmMinutes);
    query.bindValue(":alarmDays", alarmDays);
    query.bindValue(":alarmActivated", alarmActivated);
    query.exec();

    qDebug()<<"Added i think?";
    qDebug()<<"SQL ERROR: "<<query.lastError().text();
}

void Alarms::updateAlarm(QString alarmUUID, QString alarmName, int alarmHour, int alarmMinutes, QString alarmDays, bool alarmActivated) {
    for ( int i = 0; i < m_list.count(); i++ ) {
        if ( m_list[i]->alarmUUID() == alarmUUID ) {
            //Get the alarm that needs updating.
            Alarm *alarmToUpdate = m_list[i];

            alarmToUpdate->setAlarmName(alarmName);
            alarmToUpdate->setAlarmHour(alarmHour);
            alarmToUpdate->setAlarmMinutes(alarmMinutes);
            alarmToUpdate->setAlarmDays(alarmDays);
            alarmToUpdate->setAlarmActivated(alarmActivated);

            emit listChanged(m_list);
            break;
        }
    }

    QSqlQuery query;
    query.prepare("UPDATE alarms SET alarmID=:alarmUUID, alarmName=:alarmName, alarmHour=:alarmHour, alarmMinutes=:alarmMinutes, alarmDays=:alarmDays, alarmActivated=:alarmActivated WHERE alarmID=:alarmUUID;");
    query.bindValue(":alarmUUID", alarmUUID);
    query.bindValue(":alarmName", alarmName);
    query.bindValue(":alarmHour", alarmHour);
    query.bindValue(":alarmMinutes", alarmMinutes);
    query.bindValue(":alarmDays", alarmDays);
    query.bindValue(":alarmActivated", alarmActivated);
    query.exec();
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

    QSqlQuery query;
    query.prepare("DELETE FROM alarms WHERE alarmID=:alarmID");
    query.bindValue(":alarmID", alarmUUID);
    query.exec();
    qDebug()<<"SQL ERROR: "<<query.lastError().text();
}
