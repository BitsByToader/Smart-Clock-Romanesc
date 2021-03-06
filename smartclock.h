#ifndef SMARTCLOCK_H
#define SMARTCLOCK_H

#include <QObject>
#include <QtSql>
#include <QDebug>

#include <alarms.h>
#include <quotemanager.h>
#include <settingsmanager.h>

class SmartClock : public QObject {
    Q_OBJECT
    Q_PROPERTY(AlarmManager* alarms READ alarms NOTIFY alarmsChanged)
    Q_PROPERTY(QuoteManager* quotes READ quotes NOTIFY quotesChanged)
    Q_PROPERTY(SettingsManager* settings READ settings NOTIFY settingsChanged)
    Q_PROPERTY(QString hour READ hour NOTIFY hourChanged)
    Q_PROPERTY(QString minute READ minute NOTIFY minuteChanged)
    Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(QString headline READ headline WRITE setHeadline NOTIFY headlineChanged)

public:
    explicit SmartClock(QObject *parent = nullptr);

    static QString makeNumberDoubleDigit(int number) {
        return ( number / 10 == 0 ) ? ("0" + QString::number(number)) : QString::number(number);
    }

    AlarmManager* alarms() const {
        return m_alarms;
    }

    SettingsManager* settings() const {
        return m_settings;
    }

    QString hour() const {
        return makeNumberDoubleDigit(m_hour);
    }

    QString minute() const {
        return makeNumberDoubleDigit(m_minute);
    }

    QString date() const {
        return m_date;
    }

    QString headline() const {
        return m_headline;
    }

    QuoteManager* quotes() const {
        return m_quotes;
    }

public slots:
    void updateSmartClockTimeAndDate(int hour, int minute, QString formattedDate);
//    void updateHeadline(QString newHeadline);
    void setHour(int hour);
    void setMinute(int minute);
    void setDate(QString date);
    void setHeadline(QString headline);

signals:
    void alarmsChanged(AlarmManager* alarms);
    void settingsChanged(SettingsManager* settings);
    void hourChanged();
    void minuteChanged();
    void dateChanged(QString date);
    void headlineChanged(QString headline);
    void quotesChanged(QuoteManager* quotes);

private:
    AlarmManager* m_alarms;
    QuoteManager* m_quotes;
    SettingsManager* m_settings;

    int m_hour = 0;
    int m_minute = 0;
    QString m_date;
    QString m_headline;
};

#endif // SMARTCLOCK_H
