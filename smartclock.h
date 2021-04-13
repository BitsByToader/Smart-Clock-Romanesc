#ifndef SMARTCLOCK_H
#define SMARTCLOCK_H

#include <QObject>

#include <alarm.h>

class SmartClock : public QObject {
    Q_OBJECT
    Q_PROPERTY(QList<Alarm*> alarms READ alarms WRITE setAlarms NOTIFY alarmsChanged)
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
    explicit SmartClock(QObject *parent = nullptr);

    QList<Alarm*> alarms() const {
        return m_alarms;
    }

public slots:
    void setAlarms(QList<Alarm*> alarms) {
        if (m_alarms == alarms)
            return;

        m_alarms = alarms;
        emit alarmsChanged(m_alarms);
    };

    void test() {
        Alarm *newAlarm = new Alarm("test", 06, 00, {"Lu"}, true);
        m_alarms.append(newAlarm);
        emit alarmsChanged(alarms());
    };

signals:
    void alarmsChanged(QList<Alarm*> alarms);

private:
    QList<Alarm*> m_alarms;
};

#endif // SMARTCLOCK_H
