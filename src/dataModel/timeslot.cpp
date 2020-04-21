#include "timeslot.h"

Timeslot::Timeslot(QObject *parent) : QObject(parent)
{

}
QString Timeslot::name()
{
    return timeslotName;
}

void Timeslot::setName(const QString &name)
{
    if (name == timeslotName)
        return;

    timeslotName = name;
    emit nameChanged();
}

QList<Module*> Timeslot::getModules() const
{
    return this->modules;
}

QList<Group*> Timeslot::getActiveGroups() const
{
    return this->activeGroups;
}

void Timeslot::setModules(QList<Module*> modules)
{
    if (this->modules == modules)
        return;

    this->modules = modules;
    emit modulesChanged(this->modules);
}

void Timeslot::setActiveGroups(QList<Group*> activeGroups)
{
    if (this->activeGroups == activeGroups)
        return;

    this->activeGroups = activeGroups;
    emit activeGroupsChanged(this->activeGroups);
}

bool Timeslot::containsActiveGroup(Group* gp){
    return activeGroups.contains(gp);
}

void Timeslot::addActiveGroup(Group* gp){
    if (activeGroups.contains(gp)){
        return;
    }
    activeGroups.append(gp);
    emit activeGroupsChanged(this->activeGroups);
}

void Timeslot::removeActiveGroup(Group* gp){
    if (activeGroups.removeAll(gp) > 0){
        emit activeGroupsChanged(this->activeGroups);
    }
}
