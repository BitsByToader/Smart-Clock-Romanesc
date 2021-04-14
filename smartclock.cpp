#include "smartclock.h"

SmartClock::SmartClock(QObject *parent) : QObject(parent) {
    this->m_alarms = new Alarms();
}
