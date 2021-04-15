#ifndef ALARMS_H
#define ALARMS_H

#include <QObject>
#include <QtDebug>
#include <QtSql>

#include "alarm.h"

class Alarms : public QObject {
    Q_OBJECT
    Q_PROPERTY(QList<Alarm*> list READ list WRITE setList NOTIFY listChanged)
    ///This implementation ^^^ of exposing a C++ list to QML has some tradeoffs.
    ///Mainly, it is not very performant when inserting, updating or deleting elements from the list
    ///because it has to completely rewrite the list. This is not a huge issue because the elements in
    ///the QList are pointers which are small in size so there's not much to copy over.
    ///The main advantage of this method is ease of use and its readability. Compared to the other methods
    ///it requires practically no boilerplate code or any other setups.
    ///For example, a QQmlListProperty requires the use of creating 7 or 8 functions for manipulating the list
    ///for every single list. Another option would be subclassing ABstractListModel for the list or something among those lines
    /// but actually needs a second extra class as well, which again is cumbersome.
    /// Thus, for a very light list with a small number of elements and that works with pointers alone, the extra perfomance code
    /// is acceptable, and not even noticable.

public:
    explicit Alarms(QObject *parent = nullptr);

    QList<Alarm*> list() const {
        return m_list;
    }

public slots:
    void setList(QList<Alarm*> list);
    void addAlarm(QString alarmName, int alarmHour, int alarmMinutes, QString alarmDays, bool alarmActivated);
    void updateAlarm(QString alarmUUID, QString alarmName, int alarmHour, int alarmMinutes, QString alarmDays, bool alarmActivated);
    void deleteAlarm(QString alarmUUID);

signals:
    void listChanged(QList<Alarm*> list);

private:
    QList<Alarm*> m_list;
};

#endif // ALARMS_H
