#ifndef SMARTCLOCK_H
#define SMARTCLOCK_H

#include <QObject>
#include <QtSql>
#include <QDebug>

#include <alarms.h>

class SmartClock : public QObject {
    Q_OBJECT
    Q_PROPERTY(Alarms* alarms READ alarms NOTIFY alarmsChanged)

public:
    explicit SmartClock(QObject *parent = nullptr);

    Alarms* alarms() const {
        return m_alarms;
    }

public slots:

signals:
    void alarmsChanged(Alarms* alarms);

private:
    Alarms* m_alarms;
};

#endif // SMARTCLOCK_H
