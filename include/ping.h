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

    QString address;
    QString args;
    bool isRunning();

private:
    QProcess *process;
    bool listening;

signals:
    void output(const QString &data);

private slots:
    void readyRead();
    void started();
    void finished(int exitCode, QProcess::ExitStatus exitStatus);
    void errorOccurred(QProcess::ProcessError error);
    void stateChanged(QProcess::ProcessState newState);
    void readyReadStandardError();
    void readyReadStandardOutput();

public slots:
    void start();
    void stop();
};

#endif // PING_H
