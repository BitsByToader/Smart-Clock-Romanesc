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
    }

    alarmTimer = new QTimer(this);
    connect(this->alarmTimer, &QTimer::timeout, this, &Alarms::checkForAlarms);
    this->alarmTimer->start(60000);
}

void Alarms::checkForAlarms() {
    QDateTime currentDate = QDateTime::currentDateTime();

    qDebug()<<"Checking for pending alarms at: "<<currentDate.time().hour()<<":"<<currentDate.time().minute();

    emit updateSmartClockTimeAndDate(currentDate.time().hour(), currentDate.time().minute(), currentDate.toString("dddd,  d MMMM yyyy"));

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
                    this->updateAlarm(alarmID, alarmName, hour, minutes, days, false);

                    ///TODO: Ring the alarm here.
                    /// When ringing the alarm, also call a function to update the alarm headline.
                    qDebug()<<"Rang only once!";
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

void Alarms::constructNewHeadline() {
    QTime currentTime= QTime::currentTime();
    QDate currentDate= QDate::currentDate();

    int minutesSinceMidnight = currentTime.hour() * 60 + currentTime.minute();
    int currentDay = currentDate.dayOfWeek();
    int nextDay = (currentDay == 7) ? 1 : currentDay + 1;

    QString newHeadline = "Nu aveti nici o alarma.";

    QSqlQuery query;
    query.prepare("SELECT alarmDays, alarmHour, alarmMinutes FROM alarms ORDER BY alarmHour * 60 + alarmMinutes;");
//    query.addBindValue(minutesSinceMidnight);
    query.exec();

    while ( query.next() ) {
        QString alarmDays = query.value(0).toString();
        qDebug()<<alarmDays;
        QStringList daysArray = alarmDays.split(" ");

        int hour = query.value(1).toInt();
        int minutes = query.value(2).toInt();

        if ( alarmDays.isEmpty() || daysArray.contains( daysOfWeekList[currentDay] ) || daysArray.contains( daysOfWeekList[nextDay] ) ) {
            bool isToday = true;

            if ( daysArray.contains( daysOfWeekList[currentDay] )  && minutesSinceMidnight > hour * 60 + minutes ) {
                //Am trecut de alarma din ziua curenta deci nu  ne intereseaza pentru headline.
                continue;
            } else if ( daysArray.contains( daysOfWeekList[currentDay] ) && minutesSinceMidnight <= hour * 60 + minutes ) {
                //Alarma se afla dupa momentul curent deci este cea mai apropriata.
                isToday = true;
            } else if ( daysArray.contains( daysOfWeekList[nextDay] ) ) {
                //Alarma este in ziua urmatoare...
                isToday = false;
            }

            QString day = isToday ? "azi" : "maine";

            newHeadline = "Urmatoarea alarma este " + day + " la ora " + makeNumberDoubleDigit(hour) + ":" + makeNumberDoubleDigit(minutes) + ".";
            break;
        }
    }

    emit updateHeadline(newHeadline);
    ///The basic principle for the logic of this method is there.
    /// However I need to tweak the conditions a bit more.
    /// But more importantly I should probably loop through the alarms twice.
    /// The first time it will check for alarms in the current day.
    /// If it didn't find anything, it will proceed to search again but check
    /// if there's anything for the next day.
}

QString Alarms::makeNumberDoubleDigit(int number) {
    return ( number / 10 == 0 ) ? ("0" + QString::number(number)) : QString::number(number);
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

    constructNewHeadline();
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

    constructNewHeadline();
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

    constructNewHeadline();
}
