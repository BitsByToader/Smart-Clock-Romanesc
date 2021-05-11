#include "smartclock.h"

SmartClock::SmartClock(QObject *parent) : QObject(parent) {
    QSqlDatabase m_dataBase = QSqlDatabase::addDatabase("QSQLITE");
    m_dataBase.setDatabaseName("db.sqlite");

    //Check for errors when opening database
    if (!m_dataBase.open())
        qDebug()<<m_dataBase.lastError()<<Qt::endl;

    if ( !m_dataBase.tables().contains("alarms") ) {
        qDebug()<<"No alarms table found!"<<Qt::endl;
        QSqlQuery query = QSqlQuery("CREATE TABLE alarms(alarmID varchar(50) NOT NULL, alarmName varchar(255), alarmHour int, alarmMinutes int, alarmDays varchar(255), alarmActivated int, PRIMARY KEY(alarmID));");
        query.exec();
//        qDebug()<<"SQL ERROR: "<<query.lastError().text();
    }

    QSqlQuery query;

    if ( !m_dataBase.tables().contains("settings") ) {
        qDebug()<<"No settings table found!";

        query = QSqlQuery("CREATE TABLE settings(key varchar(255), value varchar(255));");
        query.exec();

        query = QSqlQuery("INSERT INTO settings(key, value) VALUES ('snooze', '10');");
        query.exec();

        query = QSqlQuery("INSERT INTO settings(key, value) VALUES ('alarmSound', 'https://www.kissfm.ro/listen.pls');");
        query.exec();
    }

    //Initialize the SettingsManager
    this->m_settings = new SettingsManager();

    //Initialize the AlarmManager
    this->m_alarms = new AlarmManager(settings());

    connect(m_alarms, &AlarmManager::updateSmartClockTimeAndDate, this, &SmartClock::updateSmartClockTimeAndDate);
    connect(m_alarms, &AlarmManager::updateHeadline, this, &SmartClock::setHeadline);

    this->m_alarms->checkForAlarms();
    this->m_alarms->constructNewHeadline();

    //Initialize the QuoteManager
    this->m_quotes = new QuoteManager();
}

void SmartClock::updateSmartClockTimeAndDate(int hour, int minute, QString formattedDate) {
    this->setHour(hour);
    this->setMinute(minute);
    this->setDate(formattedDate);
}

void SmartClock::setHour(int hour) {
    if ( hour == this->hour() )
        return;

    m_hour = hour;
    emit hourChanged();
}

void SmartClock::setMinute(int minute) {
    if ( minute == this->minute() )
        return;

    m_minute = minute;
    emit minuteChanged();
}

void SmartClock::setDate(QString date) {
    if (m_date == date)
        return;

    m_date = date;
    emit dateChanged(m_date);
}

void SmartClock::setHeadline(QString headline) {
    if (m_headline == headline)
        return;

    m_headline = headline;
    emit headlineChanged(m_headline);
}
