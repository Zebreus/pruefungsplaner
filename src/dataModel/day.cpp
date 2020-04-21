#include "day.h"

Day::Day(QObject *parent) : QObject(parent)
{

}

QString Day::name()
{
    return dayName;
}

void Day::setName(const QString &name)
{
    if (name == dayName)
        return;

    dayName = name;
    emit nameChanged();
}

QList<Timeslot*> Day::getTimeslots() const
{
    return this->timeslots;
}

void Day::setTimeslots(QList<Timeslot*> timeslots)
{
    if (this->timeslots == timeslots)
        return;

    this->timeslots = timeslots;
    emit timeslotsChanged(this->timeslots);
}
