#include "pruefungsplanermanager.h"

#include <QQmlEngine>

void addTimeslots(Day* day){
    QList<Timeslot*> timeslots;

    timeslots.append(new Timeslot(day));
    timeslots.last()->setName("1");
    timeslots.append(new Timeslot(day));
    timeslots.last()->setName("2");
    timeslots.append(new Timeslot(day));
    timeslots.last()->setName("3");
    timeslots.append(new Timeslot(day));
    timeslots.last()->setName("4");
    timeslots.append(new Timeslot(day));
    timeslots.last()->setName("5");
    timeslots.append(new Timeslot(day));
    timeslots.last()->setName("6");

    day->setTimeslots(timeslots);
}

void addDays(Week* week){
    QList<Day*> days;

    days.append(new Day(week));
    days.last()->setName("Montag");
    addTimeslots(days.last());
    days.append(new Day(week));
    days.last()->setName("Dienstag");
    addTimeslots(days.last());
    days.append(new Day(week));
    days.last()->setName("Mittwoch");
    addTimeslots(days.last());
    days.append(new Day(week));
    days.last()->setName("Donnerstag");
    addTimeslots(days.last());
    days.append(new Day(week));
    days.last()->setName("Freitag");
    addTimeslots(days.last());
    days.append(new Day(week));
    days.last()->setName("Samstag");
    addTimeslots(days.last());

    week->setDays(days);
}

Plan* createPlan(QObject* parent){
    Plan* m_plan;
    m_plan = new Plan(parent);
    m_plan->setName("Plan b");

    Module* module_a = new Module(m_plan);
    module_a->setName("Module a");
    module_a->setNumber("30.1234");
    module_a->setOrigin("FBI");
    module_a->setActive(true);
    Module* module_b = new Module(m_plan);
    module_b->setName("Module b");
    module_b->setNumber("30.1235");
    module_b->setOrigin("FBI");
    module_b->setActive(false);

    QList<Module*> modules;
    modules.append(module_a);
    modules.append(module_b);
    modules.append(module_b);
    m_plan->setModules(modules);

    Group* constraint_a = new Group(m_plan);
    constraint_a->setName("Constraint a");
    Group* constraint_b = new Group(m_plan);
    constraint_b->setName("Constraint b");
    Group* constraint_c = new Group(m_plan);
    constraint_c->setName("Constraint c");
    Group* constraint_d = new Group(m_plan);
    constraint_d->setName("Constraint d");

    QList<Group*> constraints;
    constraints.append(constraint_a);
    constraints.append(constraint_b);
    constraints.append(constraint_c);
    constraints.append(constraint_d);
    m_plan->setConstraints(constraints);
    QList<Group*> constraintsA;
    constraintsA.append(constraint_a);
    constraintsA.append(constraint_b);
    constraintsA.append(constraint_b);
    constraintsA.append(constraint_d);
    module_a->setConstraints(constraintsA);
    QList<Group*> constraintsB;
    constraintsB.append(constraint_b);
    constraintsB.append(constraint_c);
    module_b->setConstraints(constraintsB);

    Group* group_a = new Group(m_plan);
    group_a->setName("group a");
    Group* group_b = new Group(m_plan);
    group_b->setName("group b");
    Group* group_c = new Group(m_plan);
    group_c->setName("group c");

    QList<Group*> groups;
    groups.append(group_a);
    groups.append(group_b);
    groups.append(group_c);
    m_plan->setGroups(groups);
    QList<Group*> groupsA;
    groupsA.append(group_a);
    groupsA.append(group_b);
    module_a->setGroups(groupsA);
    QList<Group*> groupsB;
    groupsB.append(group_a);
    module_b->setGroups(groupsB);

    Week* week_a = new Week(m_plan);
    week_a->setName("Week a");
    Week* week_b = new Week(m_plan);
    week_b->setName("Week b");
    Week* week_c = new Week(m_plan);
    week_c->setName("Week c");

    addDays(week_a);
    addDays(week_b);
    addDays(week_c);
    QList<Week*> weeks;
    weeks.append(week_a);
    weeks.append(week_b);
    weeks.append(week_c);
    m_plan->setWeeks(weeks);

    QList<Group*> activeGroups;
    activeGroups.append(constraint_a);
    activeGroups.append(constraint_c);
    activeGroups.append(group_b);
    week_a->getDays().first()->getTimeslots().first()->setActiveGroups(activeGroups);
    week_a->getDays().last()->getTimeslots().last()->setActiveGroups(activeGroups);
    week_b->getDays().last()->getTimeslots().first()->setActiveGroups(activeGroups);
    week_c->getDays().first()->getTimeslots().last()->setActiveGroups(activeGroups);

    QJsonObject plan = m_plan->toJsonObject();

    Plan* plan_b = new Plan(parent);
    plan_b->fromJsonObject(plan);
    QJsonObject planb = plan_b->toJsonObject();

    //qDebug() << plan;
    //qDebug() << planb;

    return plan_b;
}

PruefungsplanerManager::PruefungsplanerManager(QObject *parent) : QObject(parent), progress(0), schedulingState(Inactive)
{
    Semester* semester_a = new Semester(this);
    //Semester* semester_b = new Semester(this);
    semester_a->setName("Semester 1");
    //semester_b->setName("Semester b");

    QList<Plan*> plans_a;
    plans_a.append(createPlan(semester_a));
    //plans_a.append(createPlan(semester_a));
    plans_a.first()->setName("Plan 1");
    //plans_a.last()->setName("plan b");
    //QList<Plan*> plans_b;
    //plans_b.append(createPlan(semester_b));
    //plans_b.append(createPlan(semester_b));
    //plans_b.first()->setName("plan c");
    //plans_b.last()->setName("plan d");

    semester_a->setPlans(plans_a);
    //semester_b->setPlans(plans_b);

    semesters.append(semester_a);
    //semesters.append(semester_b);
    activeSemester = semesters.first();
    activePlan = activeSemester->getPlans().first();
    connect(&autosaveTimer, &QTimer::timeout, this, &PruefungsplanerManager::saveSemesters);
    client = nullptr;
}

PruefungsplanerManager* PruefungsplanerManager::instance = nullptr;

PruefungsplanerManager* PruefungsplanerManager::getInstance()
{
    if (PruefungsplanerManager::instance == nullptr)
        instance = new PruefungsplanerManager;
    return instance;
}

QObject* PruefungsplanerManager::getQmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    return PruefungsplanerManager::getInstance();
}

void PruefungsplanerManager::setConfiguration(QSharedPointer<Configuration> configuration)
{
    this->configuration = configuration;
}

void PruefungsplanerManager::setPlanerClient(QSharedPointer<Client> planerClient)
{
    if(this->client == nullptr){
        client = planerClient;
        connect(client.data(), &Client::gotResult, this, &PruefungsplanerManager::gotResult);
        //connect(client.data(), &Client::finishedPlanning, this, &PruefungsplanerManager::gotFinishedPlan);
        //connect(client.data(), &Client::setProgress, this, &PruefungsplanerManager::gotProgress);
        client->updatePlan();
    }else{
        //TODO This should be done in a more appropriate way
        throw "Set client again";
    }
}

QString PruefungsplanerManager::userName()
{
    return m_userName;
}

QAbstractListModel* PruefungsplanerManager::testList(){
    std::cout << "A" << std::endl;
    QQuickView view;
    view.setSource(QUrl::fromLocalFile("../pruefungsplaner/dummydata/ModulesModel.qml"));
    view.show();
    QObject *object = (QObject*)view.rootObject();
    std::cout << "B" << std::endl;
    return ((QAbstractListModel*)object);
}

Plan* PruefungsplanerManager::getActivePlan(){
    return activePlan;
}

void PruefungsplanerManager::setActivePlan(Plan *plan)
{
    if (this->activePlan == plan)
        return;

    this->activePlan = plan;
    emit activePlanChanged();
}

Semester* PruefungsplanerManager::getActiveSemester(){
    return activeSemester;
}

void PruefungsplanerManager::setActiveSemester(Semester *semester)
{
    if (this->activeSemester == semester)
        return;

    this->activeSemester = semester;
    emit activeSemesterChanged();
}

void PruefungsplanerManager::setSemesters(QList<Semester*> semesters)
{
    if (this->semesters == semesters)
        return;

    this->semesters = semesters;
    emit semestersChanged(this->semesters);
}

QList<Semester*> PruefungsplanerManager::getSemesters() const
{
    return semesters;
}

void PruefungsplanerManager::setUserName(const QString &userName)
{
    if (userName == m_userName)
        return;

    m_userName = userName;
    emit userNameChanged();
}

int PruefungsplanerManager::getProgress() const
{
    qDebug() << "Get progress" << progress;
    return progress;
}

void PruefungsplanerManager::saveSemesters()
{
    QJsonArray jsonSemesters;
    for(Semester* sp : semesters){
        jsonSemesters.append(sp->toJsonObject());
    }
    client->save(jsonSemesters);
}

void PruefungsplanerManager::startPlanning(QString mode)
{
    qDebug() << "start planning";

    //Remove old scheduled Exams from plan
    //TODO Maybe do this somewhere else
    for(auto& week : activePlan->getWeeks()){
        for(auto& day : week->getDays()){
            for(auto& timeslot : day->getTimeslots()){
                timeslot->setModules(QList<Module*>());
            }
        }
    }

    SchedulerClient::SchedulingMode schedulingMode = SchedulerClient::Fast;
    if(mode == "legacy-good"){
        schedulingMode = SchedulerClient::Good;
    }

    QJsonObject plan = getActivePlan()->toJsonObject();
    if(progress == 100 || schedulerClient == nullptr){
        gotProgress(0);
        schedulerClient.reset(new SchedulerClient(configuration->getSchedulerUrl(), plan, schedulingMode));
        connect(schedulerClient.get(), &SchedulerClient::schedulingComplete, this, &PruefungsplanerManager::gotFinishedPlan);
        connect(schedulerClient.get(), &SchedulerClient::connectionFailed, this, &PruefungsplanerManager::showErrorMessage);
        connect(schedulerClient.get(), &SchedulerClient::schedulingFailed, this, &PruefungsplanerManager::showErrorMessage);
        connect(schedulerClient.get(), &SchedulerClient::warning, this, &PruefungsplanerManager::showWarningMessage);
        connect(schedulerClient.get(), &SchedulerClient::progressChanged, [this](double progress){gotProgress(progress*100);});

        auto schedulingFailed = [this](){
            schedulingState = Failed;
            emit schedulingStateChanged(schedulingState);
        };
        auto schedulingFinished = [this](){
            schedulingState = Finished;
            emit schedulingStateChanged(schedulingState);
        };
        connect(schedulerClient.get(), &SchedulerClient::connectionFailed, this, schedulingFailed);
        connect(schedulerClient.get(), &SchedulerClient::schedulingFailed, this, schedulingFailed);
        connect(schedulerClient.get(), &SchedulerClient::schedulingComplete, this, schedulingFinished);

        schedulingState = Running;
        emit schedulingStateChanged(schedulingState);

        schedulerClient->startScheduling();
    }
}

void PruefungsplanerManager::stopPlanning()
{
    if(!schedulerClient.isNull()){
        schedulerClient->abortScheduling();
    }
}

PruefungsplanerManager::SchedulingState PruefungsplanerManager::getSchedulingState() const
{
    return schedulingState;
}

void PruefungsplanerManager::gotResult(QJsonValue result)
{
    qDebug() << "Received: " << result;
    if(result.isArray()){
        semesters.clear();
        QJsonArray resultArray = result.toArray();
        for(QJsonValue val : resultArray){
            Semester* semester = new Semester(this);
            semester->fromJsonObject(val.toObject());
            semesters.append(semester);
        }
        activeSemester = semesters.first();
        activePlan = activeSemester->getPlans().first();
        emit semestersChanged(semesters);
        emit activeSemesterChanged();
        emit activePlanChanged();
    }else{
        qDebug() << "No array";
    }
    autosaveTimer.start(10000);
    //activeSemester = semesters.first();
    //m_plan = activeSemester->getPlans().first();
}

void PruefungsplanerManager::gotFinishedPlan(QJsonValue plan)
{
    qDebug() << "got finished plan";
    getActivePlan()->fromJsonObject(plan.toObject());
    emit activePlanChanged();
}

void PruefungsplanerManager::gotProgress(int progress)
{
    this->progress = progress;
    emit progressChanged(progress);
}

void PruefungsplanerManager::createNewSemester(QString name, Semester *base)
{
    Semester* newSemester = new Semester(this);
    if(base != nullptr){
        //TODO wont work
        newSemester->fromJsonObject(base->toJsonObject());
    }
    newSemester->setName(name);
    this->semesters.append(newSemester);
    emit semestersChanged(this->semesters);
}
