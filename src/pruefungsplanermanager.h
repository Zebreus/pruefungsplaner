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
#include "schedulerclient.h"
#include "configuration.h"

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
    Q_PROPERTY(SchedulingState schedulingState READ getSchedulingState NOTIFY schedulingStateChanged)

public:
    enum SchedulingState{
        Inactive,
        Running,
        Failed,
        Finished
    };
    Q_ENUM(SchedulingState)
    static PruefungsplanerManager* getInstance();
    static QObject* getQmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);
    void setConfiguration(QSharedPointer<Configuration> configuration);
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
    Q_INVOKABLE void startPlanning(QString mode = "legacy-fast");
    Q_INVOKABLE void stopPlanning();
    SchedulingState getSchedulingState() const;

signals:
    void userNameChanged();
    void activePlanChanged();
    void activeSemesterChanged();
    void semestersChanged(QList<Semester*> semesters);
    void progressChanged(int progress);
    void showErrorMessage(QString message);
    void showWarningMessage(QString message);
    void schedulingStateChanged(SchedulingState schedulingState);

public slots:
    void gotResult(QJsonValue result);
    void gotFinishedPlan(QJsonValue plan);
    void gotProgress(int progress);
    void createNewSemester(QString name, Semester* base);
    void saveSemesters();

private:
    explicit PruefungsplanerManager(QObject *parent = nullptr);
    static PruefungsplanerManager* instance;
    QString m_userName;
    Plan* activePlan;
    Semester* activeSemester;
    QList<Semester*> semesters;
    QSharedPointer<Client> client;
    int progress;
    QTimer autosaveTimer;
    QSharedPointer<SchedulerClient> schedulerClient;
    QSharedPointer<Configuration> configuration;
    SchedulingState schedulingState;
};

#endif // PRUEFUNGSPLANERBACKEND_H
