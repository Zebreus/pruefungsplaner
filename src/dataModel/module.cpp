#include "module.h"

Module::Module(QObject *parent) : SerializableDataObject(parent)
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

QString Module::getNumber()
{
    return number;
}

void Module::setNumber(const QString &number)
{
    if (number == this->number)
        return;

    this->number = number;
    emit numberChanged();
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
    if (removed > 0){
        emit groupsChanged(this->groups);
    }
}

void Module::removeConstraint(Group* constraint){

    int removed = constraints.removeAll(constraint);
    //int removed = 0;
    if (removed > 0){
        emit constraintsChanged(this->constraints);
    }
}


void Module::fromJsonObject(const QJsonObject &content)
{
    simpleValuesFromJsonObject(content);

    Plan* activePlan = (Plan*) this->parent();

    QJsonArray groupIdArray = content.value("groups").toArray();
    for(QJsonValueRef groupId: groupIdArray){
        int groupIdInt = groupId.toInt();

        // Find the group with matching id and add reference to groups
        for( Group* group : activePlan->getGroups() ){
            if(group->getId() == groupIdInt){
                groups.push_back(group);
            }
        }
    }

    QJsonArray constraintIdArray = content.value("constraints").toArray();
    for(QJsonValueRef constraintId: constraintIdArray){
        int constraintIdInt = constraintId.toInt();

        // Find the constraint with matching id and add reference to constraints
        for( Group* constraint : activePlan->getConstraints() ){
            if(constraint->getId() == constraintIdInt){
                constraints.push_back(constraint);
            }
        }
    }

}

QJsonObject Module::toJsonObject() const
{
    QJsonObject jsonObject = recursiveToJsonObject();

    QJsonArray groupArray;
    for(QJsonValueRef group: jsonObject.value("groups").toArray()){
        int groupId = group.toObject().value("id").toInt();
        groupArray.push_back(groupId);
    }
    jsonObject.insert("groups", groupArray);

    QJsonArray constraintArray;
    for(QJsonValueRef group: jsonObject.value("constraints").toArray()){
        int groupId = group.toObject().value("id").toInt();
        constraintArray.push_back(groupId);
    }
    jsonObject.insert("constraints", constraintArray);

    return jsonObject;
}
