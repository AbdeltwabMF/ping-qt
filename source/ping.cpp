#include <QByteArray>

#include <QDebug>

#include "../include/ping.h"

Ping::Ping(QObject *parent)
    : QObject{parent}
{
    process = new QProcess;

    connect(process, &QProcess::started, this, &Ping::onStarted);
    connect(process, &QProcess::stateChanged, this, &Ping::onStateChanged);
    connect(process, &QProcess::readyRead, this, &Ping::read);
    connect(process, &QProcess::readyReadStandardOutput, this, &Ping::readStandardOutput);
    connect(process, &QProcess::errorOccurred, this, &Ping::onErrorOccurred);
    connect(process, &QProcess::readyReadStandardError, this, &Ping::readStandardError);
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &Ping::onFinished);
}

// Public slots
void Ping::start(const QString &address, const QString &args)
{
    qInfo() << Q_FUNC_INFO;
    listening = true;
    QStringList processArgs = {address, args};
    process->start("ping", processArgs);
}

void Ping::stop()
{
    qInfo() << Q_FUNC_INFO;
    listening = false;
    process->close();
}

// Private slots
void Ping::onStarted()
{
    qInfo() << Q_FUNC_INFO;
    emit started();
}

void Ping::onStateChanged(QProcess::ProcessState newState)
{
    qInfo() << Q_FUNC_INFO;
    switch (newState)
    {
    case QProcess::NotRunning:
        break;
    case QProcess::Starting:
        break;
    case QProcess::Running:
        break;
    }
}

void Ping::onErrorOccurred(QProcess::ProcessError error)
{
    if(listening == false) return;
    qInfo() << Q_FUNC_INFO;
    emit output("Error occurred");
}

void Ping::readStandardError()
{
    if(listening == false) return;
    qInfo() << Q_FUNC_INFO;
    QByteArray stdErr = process->readAllStandardError();
    emit output(stdErr.trimmed());
}

void Ping::read()
{
    if(listening == false) return;
    qInfo() << Q_FUNC_INFO;
    QByteArray result = process->readAll();
    emit output(result.trimmed());
}

void Ping::readStandardOutput()
{
    if(listening == false) return;
    qInfo() << Q_FUNC_INFO;
    QByteArray stdOut = process->readAllStandardOutput();
    emit output(stdOut.trimmed());
}

void Ping::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qInfo() << Q_FUNC_INFO;
    Q_UNUSED(exitCode);
    Q_UNUSED(exitStatus);
    emit output("Complete");
    emit finished();
}
