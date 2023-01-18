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

private:
    QProcess *process;
    bool listening;

signals:
    void output(const QString &data);
    void started();
    void finished();

private slots:
    void read();
    void onStarted();
    void onFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onErrorOccurred(QProcess::ProcessError error);
    void onStateChanged(QProcess::ProcessState newState);
    void readStandardError();
    void readStandardOutput();

public slots:
    void start(const QString &address, const QString &args);
    void stop();
};

#endif // PING_H
