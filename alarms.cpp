#include "alarms.h"

AlarmManager::AlarmManager(QObject *parent) : QObject(parent) {
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
        m_alarmsHash.insert(alarmToAdd->alarmUUID(), alarmToAdd);
    }

    alarmTimer = new QTimer(this);
    connect(this->alarmTimer, &QTimer::timeout, this, &AlarmManager::checkForAlarms);

    QTimer syncTimer(this);
    syncTimer.setTimerType(Qt::PreciseTimer);

    //Add an extra second to the sync Timer so it doesn't fire off to quickly and remain 1 minute behind.
    syncTimer.singleShot((60 - QTime::currentTime().second() + 1 )*1000, this, &AlarmManager::syncTimer);

}

void AlarmManager::checkForAlarms() {
    QDateTime currentDate = QDateTime::currentDateTime();

    qDebug()<<"Checking for pending alarms at: "<<currentDate.time().hour()<<":"<<currentDate.time().minute();

    emit updateSmartClockTimeAndDate(currentDate.time().hour(), currentDate.time().minute(), currentDate.toString("dddd,  d MMMM yyyy"));

    if ( alarmSnoozed ) {
        //There is a snoozed alarm, take care of it first.
        int minutesSinceMidnight = currentDate.time().hour() * 60 + currentDate.time().minute();

        if ( timeToRing == minutesSinceMidnight ) {
            qDebug()<<"Snoozed alarm rang!";

            alarmSnoozed = false;
            emit ringAlarmUI();

            return;
        }
    }

    QSqlQuery query("SELECT alarmHour, alarmMinutes, alarmDays, alarmActivated, alarmID, alarmName FROM alarms;");

    while ( query.next() ) {
        int hour = query.value(0).toInt();
        int minutes = query.value(1).toInt();
        QString days = query.value(2).toString();
        QStringList daysArray = days.split(" ");
        bool activated = query.value(3).toInt();
        QString alarmID = query.value(4).toString();
        QString alarmName = query.value(5).toString();

        if ( activated ) {
            if ( hour == currentDate.time().hour() && minutes == currentDate.time().minute() ) {
                if ( days.isEmpty() ) {
                    //If the array is empty then the alarm shouldn't repeat so we disable it.
                    qDebug()<<"Rang only once!";
                    emit ringAlarmUI();

                    this->updateAlarm(alarmID, alarmName, hour, minutes, days, false);

                    break;
                } else if ( daysArray.contains( daysOfWeekList[currentDate.date().dayOfWeek()] ) ) {
                    //The array isn't empty and we are in the correct day to ring the alarm.

                    qDebug()<<"Rang!";
                    emit ringAlarmUI();

                    break;
                }

                //We aren't in the correct day, so we don't ring the alarm...
            }
        }
    }
}

void AlarmManager::constructNewHeadline() {
    QTime currentTime= QTime::currentTime();
    QDate currentDate= QDate::currentDate();

    int minutesSinceMidnight = currentTime.hour() * 60 + currentTime.minute();
    int currentDay = currentDate.dayOfWeek();
    int nextDay = ( currentDay == 7 ) ? 1 : currentDay + 1;

    QString newHeadline = "Nu aveti nici o alarma.";

    if ( alarmSnoozed ) {
        QString hour = makeNumberDoubleDigit(timeToRing / 60);
        QString minute = makeNumberDoubleDigit(timeToRing % 60);

        newHeadline = "Alarma amanata va suna la ora " + hour + ":" + minute + ".";
        emit updateHeadline(newHeadline);

        return;
    }

    QSqlQuery query;
    query.prepare("SELECT alarmDays, alarmHour, alarmMinutes, alarmActivated, alarmID FROM alarms ORDER BY alarmHour * 60 + alarmMinutes;");
    query.exec();

    bool foundAlarmOnCurrDay = false;
    nextAlarmToRing = nullptr;

    while ( query.next() ) {
        //First loop to scan for alarms in the current day.
        QString alarmDays = query.value(0).toString();
        QStringList daysArray = alarmDays.split(" ");

        int hour = query.value(1).toInt();
        int minutes = query.value(2).toInt();
        bool alarmActivated = query.value(3).toInt();
        QString alarmID = query.value(4).toString();

        if ( alarmActivated ) {
            if ( alarmDays.isEmpty() || daysArray.contains( daysOfWeekList[currentDay] ) ) {
                if ( minutesSinceMidnight < hour * 60 + minutes ) {
                    foundAlarmOnCurrDay = true;
                    nextAlarmToRing = m_alarmsHash[alarmID];

                    newHeadline = "Urmatoarea alarma este azi la ora " + makeNumberDoubleDigit(hour) + ":" + makeNumberDoubleDigit(minutes) + ".";

                    break;
                }
            }
        }
    }

    if  ( !foundAlarmOnCurrDay ) {
        query.exec();

        while ( query.next() ) {
            //Second loop to scan for alarms in the next day.
            QString alarmDays = query.value(0).toString();
            QStringList daysArray = alarmDays.split(" ");

            int hour = query.value(1).toInt();
            int minutes = query.value(2).toInt();
            bool alarmActivated = query.value(3).toInt();
            QString alarmID = query.value(4).toString();

            if ( alarmActivated ) {
                if ( alarmDays.isEmpty() || daysArray.contains( daysOfWeekList[nextDay] ) ) {
                    newHeadline = "Urmatoarea alarma este maine la ora " + makeNumberDoubleDigit(hour) + ":" + makeNumberDoubleDigit(minutes) + ".";
                    nextAlarmToRing = m_alarmsHash[alarmID];

                    break;
                }
            }
        }
    }

    emit nextAlarmChanged(nextAlarmToRing);
    emit updateHeadline(newHeadline);
}

void AlarmManager::cancelNextAlarm() {
    if ( !alarmSnoozed ) {
        updateAlarm(nextAlarmToRing->alarmUUID(),
                    nextAlarmToRing->alarmName(),
                    nextAlarmToRing->alarmHour(),
                    nextAlarmToRing->alarmMinutes(),
                    nextAlarmToRing->alarmDays(),
                    false);
        nextAlarmToRing = nullptr;
    }

    alarmSnoozed = false;

    emit nextAlarmChanged(nextAlarmToRing);
    constructNewHeadline();
}

void AlarmManager::snoozeAlarm() {
    alarmSnoozed = true;

    QTime currentTime = QTime::currentTime();
    int minutesSinceMidnight = currentTime.hour() * 60 + currentTime.minute();
    timeToRing = minutesSinceMidnight + 10;
    ///TODO: Make the snooze time user configurable

    constructNewHeadline();
}

//Function that gets called only once at the start of the minute to sync the timer to the system clock.
void AlarmManager::syncTimer() {
    qDebug()<<"Syncing timer...";
    this->alarmTimer->start(60000);
    this->checkForAlarms();
}

QString AlarmManager::makeNumberDoubleDigit(int number) {
    return ( number / 10 == 0 ) ? ("0" + QString::number(number)) : QString::number(number);
}

void AlarmManager::setList(QList<Alarm *> list) {
    if (m_list == list)
        return;

    m_list = list;
    emit listChanged(m_list);
}

void AlarmManager::addAlarm(QString alarmName, int alarmHour, int alarmMinutes, QString alarmDays, bool alarmActivated) {
    Alarm *newAlarm = new Alarm(alarmName, alarmHour, alarmMinutes, alarmDays, alarmActivated);

    m_list.append(newAlarm);
    m_alarmsHash.insert(newAlarm->alarmUUID(), newAlarm);
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

    constructNewHeadline();
}

void AlarmManager::updateAlarm(QString alarmUUID, QString alarmName, int alarmHour, int alarmMinutes, QString alarmDays, bool alarmActivated) {
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

    constructNewHeadline();
}

void AlarmManager::deleteAlarm(QString alarmUUID) {
    for ( int i = 0; i < m_list.count(); i++ ) {
        if ( m_list[i]->alarmUUID() == alarmUUID ) {
            //Remove the alarm from the alarmsHash before removing from the list so we can get the UUID.
            m_alarmsHash.remove(m_list[i]->alarmUUID());

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

    constructNewHeadline();
}
