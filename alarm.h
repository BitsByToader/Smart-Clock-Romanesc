#ifndef ALARM_H
#define ALARM_H

#include <QObject>
#include <QDebug>
#include <QUuid>

class Alarm : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString alarmName READ alarmName WRITE setAlarmName NOTIFY alarmNameChanged)
    Q_PROPERTY(int alarmHour READ alarmHour WRITE setAlarmHour NOTIFY alarmHourChanged)
    Q_PROPERTY(int alarmMinutes READ alarmMinutes WRITE setAlarmMinutes NOTIFY alarmMinutesChanged)
    Q_PROPERTY(QString alarmDays READ alarmDays WRITE setAlarmDays NOTIFY alarmDaysChanged)
    Q_PROPERTY(bool alarmActivated READ alarmActivated WRITE setAlarmActivated NOTIFY alarmActivatedChanged)
    Q_PROPERTY(QString alarmUUID READ alarmUUID)

public:
    Alarm(QObject *parent = nullptr);
    explicit Alarm(QString alarmName, int alarmHour, int alarmMinutes, QString alarmDays, bool alarmActivated, QObject *parent = nullptr);

    QString alarmName() const {
        return m_alarmName;
    };

    int alarmHour() const {
        return m_alarmHour;
    };

    int alarmMinutes() const {
        return m_alarmMinutes;
    };

    QString alarmDays() const {
        return m_alarmDays;
    };

    bool alarmActivated() const {
        return m_alarmActivated;
    };

    QString alarmUUID() const {
        return m_alarmUUID;
    };


public slots:
    void setAlarmName(QString alarmName);
    void setAlarmHour(int alarmHour);
    void setAlarmMinutes(int alarmMinutes);
    void setAlarmDays(QString alarmDays);
    void setAlarmActivated(bool alarmActivated);
    void setAlarmUUID(const QString &alarmUUID);

signals:
    void alarmNameChanged(QString alarmName);
    void alarmHourChanged(int alarmHour);
    void alarmMinutesChanged(int alarmMinutes);
    void alarmDaysChanged(QString alarmDays);
    void alarmActivatedChanged(bool alarmActivated);

private:
    QString m_alarmName;
    int m_alarmHour;
    int m_alarmMinutes;
    QString m_alarmDays;
    bool m_alarmActivated;
    QString m_alarmUUID;
};

#endif // ALARM_H
