#ifndef MODULE_H
#define MODULE_H

#include <QObject>
#include <QString>
#include <QQmlListProperty>
#include <QList>
#include "group.h"
#include <vector>
#include <iostream>

using namespace std;

class Module : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString origin READ getOrigin WRITE setOrigin NOTIFY originChanged)
    Q_PROPERTY(QString id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(bool active READ getActive WRITE setActive NOTIFY activeChanged)

    Q_PROPERTY(QList<Group*> constraints READ getConstraints WRITE setConstraints NOTIFY constraintsChanged)
    Q_PROPERTY(QList<Group*> groups READ getGroups WRITE setGroups NOTIFY groupsChanged)

public:
    explicit Module(QObject *parent = nullptr);
    QString getName();
    void setName(const QString &name);
    QString getOrigin();
    void setOrigin(const QString &origin);
    QString getId();
    void setId(const QString &id);
    bool getActive();
    void setActive(const bool active);
    QList<Group*> getConstraints();
    QList<Group*> getGroups() const;
    void setConstraints(QList<Group*> constraints);
    void setGroups(QList<Group*> groups);


signals:
    void nameChanged();
    void originChanged();
    void idChanged();
    void activeChanged();
    void constraintsChanged(QList<Group*> groups);
    void groupsChanged(QList<Group*> groups);

public slots:
    void removeGroup(Group* group);
    void removeConstraint(Group* constraint);
public:
    QString name;
    QString origin;
    QString id;
    bool active;
    QList<Group*> constraints;
    QList<Group*> groups;
};

#endif // MODULE_H
