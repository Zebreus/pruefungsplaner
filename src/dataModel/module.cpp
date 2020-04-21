#include "module.h"

Module::Module(QObject *parent) : QObject(parent)
{

}
QString Module::getName()
{
    return name;
}

void Module::setName(const QString &name)
{
    if (name == this->name)
        return;

    this->name = name;
    emit nameChanged();
}

QString Module::getOrigin()
{
    return origin;
}

void Module::setOrigin(const QString &origin)
{
    if (origin == this->origin)
        return;

    this->origin = origin;
    emit originChanged();
}

QString Module::getId()
{
    return id;
}

void Module::setId(const QString &id)
{
    if (id == this->id)
        return;

    this->id = id;
    emit idChanged();
}

bool Module::getActive()
{
    return active;
}

void Module::setActive(const bool active)
{
    if (active == this->active)
        return;

    this->active = active;
    emit activeChanged();
}

QList<Group*> Module::getConstraints(){
    return constraints;
}

void Module::setConstraints(QList<Group*> constraints)
{
    if (this->constraints == constraints)
        return;

    this->constraints = constraints;
    emit constraintsChanged(this->constraints);
}

QList<Group*> Module::getGroups() const
{
    return groups;
}

void Module::setGroups(QList<Group*> groups)
{
    if (this->groups == groups)
        return;

    this->groups = groups;
    emit groupsChanged(this->groups);
}

void Module::removeGroup(Group* group){

    int removed = groups.removeAll(group);
    //int removed = 0;
    cout << removed << " groups removed" << group << endl;
    if (removed > 0){
        emit groupsChanged(this->groups);
    }
}

void Module::removeConstraint(Group* constraint){

    int removed = constraints.removeAll(constraint);
    //int removed = 0;
    cout << removed << " constraints removed" << constraint << endl;
    if (removed > 0){
        emit constraintsChanged(this->constraints);
    }
}
