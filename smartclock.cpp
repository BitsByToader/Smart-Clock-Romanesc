#include "smartclock.h"

SmartClock::SmartClock(QObject *parent) : QObject(parent) {
    Alarm *alarm1 = new Alarm("alarma1", 6, 30, {"Lu", "Ma"}, true);
    Alarm *alarm2 = new Alarm("scoala", 8, 00, {"Lu", "Ma"}, false);
    Alarm *alarm3 = new Alarm("viata", 9, 45, {"Lu", "Ma", "Mi"}, true);

    m_alarms.append(alarm1);
    m_alarms.append(alarm2);
    m_alarms.append(alarm3);
}
