#include "group.h"

Group::Group(QObject *parent) : QObject(parent)
{

}

QString Group::name()
{
    return constraintName;
}

void Group::setName(const QString &name)
{
    if (name == constraintName)
        return;

    constraintName = name;
    emit nameChanged();
}

bool Group::getSelected()
{
    return selected;
}

void Group::setSelected(const bool selected)
{
    if (selected == this->selected)
        return;

    this->selected = selected;
    emit selectedChanged();
}
