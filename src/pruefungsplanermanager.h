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
#include <plan.h>
#include <semester.h>
#include <day.h>
#include <group.h>
#include <module.h>
#include <timeslot.h>
#include <week.h>
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
    Q_PROPERTY(int progress READ getProgress NOTIFY progressChanged)

public:
    static PruefungsplanerManager* getInstance();
    static QObject* getQmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);
    void setPlanerClient(QSharedPointer<Client> planerClient);
    QAbstractListModel* testList();
    QString userName();
    Plan* getActivePlan();
    void setActivePlan(Plan* plan);
    Semester* getActiveSemester();
    void setActiveSemester(Semester* semester);
    QList<Semester*> getSemesters() const;
    void setSemesters(QList<Semester*> semesters);
    void setUserName(const QString &userName);
    int getProgress() const;
    Q_INVOKABLE void startPlanning();

signals:
    void userNameChanged();
    void activePlanChanged();
    void activeSemesterChanged();
    void semestersChanged(QList<Semester*> semesters);
    void progressChanged(int progress);

public slots:
    void gotResult(QJsonValue result);
    void gotFinishedPlan(QJsonValue plan);
    void gotProgress(int progress);
    void saveSemesters();

private:
    explicit PruefungsplanerManager(QObject *parent = nullptr);
    static PruefungsplanerManager* instance;
    QString m_userName;
    Plan* m_plan;
    Semester* activeSemester;
    QList<Semester*> semesters;
    QSharedPointer<Client> client;
    int m_progress;
    QTimer autosaveTimer;

};

#endif // PRUEFUNGSPLANERBACKEND_H
