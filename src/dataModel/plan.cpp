#include "plan.h"

Plan::Plan(QObject *parent) : QObject(parent)
{

}
QString Plan::name()
{
    return planName;
}

void Plan::setName(const QString &name)
{
    if (name == planName)
        return;

    planName = name;
    emit nameChanged();
}

QList<Group*> Plan::getConstraints(){
    return constraints;
}

QList<Group*> Plan::getGroups() const
{
    return groups;
}

void Plan::setConstraints(QList<Group*> constraints)
{
    if (this->constraints == constraints)
        return;

    this->constraints = constraints;
    emit constraintsChanged(this->constraints);
}
void Plan::setGroups(QList<Group*> groups)
{
    if (this->groups == groups)
        return;

    this->groups = groups;
    emit groupsChanged(this->groups);
}


QList<Module*> Plan::getModules(){
    return modules;
}

QList<Week*> Plan::getWeeks() const
{
    return this->weeks;
}

void Plan::setWeeks(QList<Week*> weeks)
{
    if (this->weeks == weeks)
        return;

    this->weeks = weeks;
    emit weeksChanged(this->weeks);
}

void Plan::addNewGroup(QString name){
//    Week* o = weeks[0];
//        QJsonObject obj;
//        auto mo = o->metaObject();
//        for (int i = mo->propertyOffset(); i < mo->propertyCount(); ++i){
//            QVariant value = mo->property(i).name();
//            obj[mo->property(i).name()] = ToJson(value);
//        }
//        //return obj;

    Group* gp = new Group(this);
    gp->setName(name);
    groups.append(gp);
    emit groupsChanged(this->groups);
}

void Plan::removeGroup(Group* gp){
    if(groups.removeAll(gp) > 0){
        for(Week* week : weeks){
            for(Day* day : week->getDays()){
                for(Timeslot* slot : day->getTimeslots()){
                    slot->removeActiveGroup(gp);
                }
            }
        }
    }
    emit groupsChanged(this->groups);
}

void Plan::addNewConstraint(QString name){
    Group* gp = new Group(this);
    gp->setName(name);
    constraints.append(gp);
    emit constraintsChanged(this->groups);
}

void Plan::removeConstraint(Group* gp){
    if(constraints.removeAll(gp) > 0){
        for(Week* week : weeks){
            for(Day* day : week->getDays()){
                for(Timeslot* slot : day->getTimeslots()){
                    slot->removeActiveGroup(gp);
                }
            }
        }
    }
    emit constraintsChanged(this->groups);
}
