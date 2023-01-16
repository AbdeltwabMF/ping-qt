#ifndef PING_H
#define PING_H

#include <QObject>
#include <QProcess>
#include <QSysInfo>

class Ping : public QObject
{
    Q_OBJECT
public:
    explicit Ping(QObject *parent = nullptr);

    QString getOsName() const;
    void startProcess(QString &address);

private:
    QProcess *process;

signals:

};

#endif // PING_H
