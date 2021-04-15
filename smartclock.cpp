#include "smartclock.h"

SmartClock::SmartClock(QObject *parent) : QObject(parent) {
    QSqlDatabase m_dataBase = QSqlDatabase::addDatabase("QSQLITE");
    m_dataBase.setDatabaseName("db.sqlite");

    //Check for errors when opening database
    if (!m_dataBase.open())
        qDebug()<<m_dataBase.lastError()<<Qt::endl;

    if ( !m_dataBase.tables().contains("alarms") ) {
        qDebug()<<"Empty database file!"<<Qt::endl;
        QSqlQuery query = QSqlQuery("CREATE TABLE alarms(alarmID varchar(50) NOT NULL, alarmName varchar(255), alarmHour int, alarmMinutes int, alarmDays varchar(255), alarmActivated int, PRIMARY KEY(alarmID));");
        query.exec();
        qDebug()<<"SQL ERROR: "<<query.lastError().text();
    }

    this->m_alarms = new Alarms();
}
