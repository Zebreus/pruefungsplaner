#ifndef PRUEFUNGSPLANER_MANAGER_H
#define PRUEFUNGSPLANER_MANAGER_H

#include <QObject>
#include <QAbstractListModel>
#include <QString>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QUrl>
#include <QQuickView>
#include <iostream>
#include "src/dataModel/plan.h"
#include "src/dataModel/semester.h"
#include "src/dataModel/day.h"
#include "src/dataModel/group.h"
#include "src/dataModel/module.h"
#include "src/dataModel/timeslot.h"
#include "src/dataModel/week.h"
#include "client.h"

class QQmlEngine;
class QJSEngine;

class PruefungsplanerManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractListModel* testList READ testList)
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(Semester* activeSemester READ getActiveSemester WRITE setActiveSemester NOTIFY activeSemesterChanged)
    Q_PROPERTY(Plan* activePlan READ getActivePlan WRITE setActivePlan NOTIFY activePlanChanged)
    Q_PROPERTY(QList<Semester*> semesters READ getSemesters WRITE setSemesters NOTIFY semestersChanged)

public:
    static PruefungsplanerManager* getInstance();
    static QObject* getQmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);
    QAbstractListModel* testList();
    QString userName();
    Plan* getActivePlan();
    void setActivePlan(Plan* plan);
    Semester* getActiveSemester();
    void setActiveSemester(Semester* semester);
    QList<Semester*> getSemesters() const;
    void setSemesters(QList<Semester*> semesters);
    void setUserName(const QString &userName);

signals:
    void userNameChanged();
    void activePlanChanged();
    void activeSemesterChanged();
    void semestersChanged(QList<Semester*> semesters);

public slots:
    void gotResult(QJsonValue result);

private:
    explicit PruefungsplanerManager(QObject *parent = nullptr);
    static PruefungsplanerManager* instance;
    QString m_userName;
    Plan* m_plan;
    Semester* activeSemester;
    QList<Semester*> semesters;
    Client* client;
};

#endif // PRUEFUNGSPLANERBACKEND_H
