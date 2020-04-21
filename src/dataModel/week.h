#ifndef WEEK_H
#define WEEK_H

#include <QObject>
#include <QString>
#include "day.h"

class Week : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QList<Day*> days READ getDays WRITE setDays NOTIFY daysChanged)
public:
    explicit Week(QObject *parent = nullptr);
    QString name();
    void setName(const QString &name);
    QList<Day*> getDays() const;
    void setDays(QList<Day*> days);

signals:
    void nameChanged();
    void daysChanged(QList<Day*> days);

private:
    QString weekName;
    QList<Day*> days;
};

#endif // WEEK_H
