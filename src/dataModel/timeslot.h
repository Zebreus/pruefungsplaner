#ifndef TIMESLOT_H
#define TIMESLOT_H

#include <QObject>
#include <QString>
#include "module.h"
#include "group.h"

class Timeslot : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QList<Module*> modules READ getModules WRITE setModules NOTIFY modulesChanged)
    Q_PROPERTY(QList<Group*> activeGroups READ getActiveGroups WRITE setActiveGroups NOTIFY activeGroupsChanged)
public:
    explicit Timeslot(QObject *parent = nullptr);
    QString name();
    void setName(const QString &name);
    QList<Module*> getModules() const;
    QList<Group*> getActiveGroups() const;
    void setModules(QList<Module*> modules);
    void setActiveGroups(QList<Group*> activeGroups);
    Q_INVOKABLE bool containsActiveGroup(Group* gp);
    Q_INVOKABLE void addActiveGroup(Group* gp);
    Q_INVOKABLE void removeActiveGroup(Group* gp);

signals:
    void nameChanged();
    void modulesChanged(QList<Module*> modules);
    void activeGroupsChanged(QList<Group*> activeGroups);

private:
    QString timeslotName;

    QList<Module*> modules;
    QList<Group*> activeGroups;
};

#endif // TIMESLOT_H
