#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <QObject>
#include <QString>

class Group : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool selected READ getSelected WRITE setSelected NOTIFY selectedChanged)
public:
    explicit Group(QObject *parent = nullptr);
    QString name();
    void setName(const QString &name);
    bool getSelected();
    void setSelected(const bool selected);

signals:
    void nameChanged();
    void selectedChanged();

private:
    QString constraintName;
    bool selected;

};

#endif // CONSTRAINT_H
