#ifndef DAY_H
#define DAY_H

#include <QObject>
#include <QString>
#include "timeslot.h"

class Day : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QList<Timeslot*> timeslots READ getTimeslots WRITE setTimeslots NOTIFY timeslotsChanged)
public:
    explicit Day(QObject *parent = nullptr);

    QString name();
    void setName(const QString &name);
    QList<Timeslot*> getTimeslots() const;
    void setTimeslots(QList<Timeslot*> timeslots);

signals:
    void nameChanged();

    void timeslotsChanged(QList<Timeslot*> timeslots);

private:
    QString dayName;

    QList<Timeslot*> timeslots;
};

#endif // DAY_H
