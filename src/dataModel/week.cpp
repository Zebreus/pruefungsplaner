#include "week.h"

Week::Week(QObject *parent) : QObject(parent)
{

}
QString Week::name()
{
    return weekName;
}

void Week::setName(const QString &name)
{
    if (name == weekName)
        return;

    weekName = name;
    emit nameChanged();
}

QList<Day*> Week::getDays() const
{
    return this->days;
}

void Week::setDays(QList<Day*> days)
{
    if (this->days == days)
        return;

    this->days = days;
    emit daysChanged(this->days);
}
