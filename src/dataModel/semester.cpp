#include "semester.h"

Semester::Semester(QObject *parent) : QObject(parent)
{

}
QString Semester::name()
{
    return semesterName;
}

void Semester::setName(const QString &name)
{
    if (name == semesterName)
        return;

    semesterName = name;
    emit nameChanged();
}

QList<Plan*> Semester::getPlans() const
{
    return this->plans;
}

void Semester::setPlans(QList<Plan*> plans)
{
    if (this->plans == plans)
        return;

    this->plans = plans;
    emit plansChanged(this->plans);
}
