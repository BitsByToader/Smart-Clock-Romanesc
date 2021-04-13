#ifndef ALARM_H
#define ALARM_H

#include <QObject>
#include <QDebug>

class Alarm : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString alarmName READ alarmName WRITE setAlarmName NOTIFY alarmNameChanged)
    Q_PROPERTY(int alarmHour READ alarmHour WRITE setAlarmHour NOTIFY alarmHourChanged)
    Q_PROPERTY(int alarmMinutes READ alarmMinutes WRITE setAlarmMinutes NOTIFY alarmMinutesChanged)
    Q_PROPERTY(QList<QString> alarmDays READ alarmDays WRITE setAlarmDays NOTIFY alarmDaysChanged)
    Q_PROPERTY(bool alarmActivated READ alarmActivated WRITE setAlarmActivated NOTIFY alarmActivatedChanged)

public:
    explicit Alarm(QString alarmName, int alarmHour, int alarmMinutes, QList<QString> alarmDays, bool alarmActivated, QObject *parent = nullptr);

    QString alarmName() const {
        return m_alarmName;
    }

    int alarmHour() const {
        return m_alarmHour;
    }

    int alarmMinutes() const {
        return m_alarmMinutes;
    }

    QList<QString> alarmDays() const {
        return m_alarmDays;
    }

    bool alarmActivated() const {
        return m_alarmActivated;
    }

public slots:
    void setAlarmName(QString alarmName);
    void setAlarmHour(int alarmHour);
    void setAlarmMinutes(int alarmMinutes);
    void setAlarmDays(QList<QString> alarmDays);
    void setAlarmActivated(bool alarmActivated);

signals:
    void alarmNameChanged(QString alarmName);
    void alarmHourChanged(int alarmHour);
    void alarmMinutesChanged(int alarmMinutes);
    void alarmDaysChanged(QList<QString> alarmDays);
    void alarmActivatedChanged(bool alarmActivated);

private:
    QString m_alarmName;
    int m_alarmHour;
    int m_alarmMinutes;
    QList<QString> m_alarmDays;
    bool m_alarmActivated;
};

#endif // ALARM_H
