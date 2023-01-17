#include <QByteArray>

#include <QDebug>

#include "../include/ping.h"

Ping::Ping(QObject *parent)
    : QObject{parent}
{
    process = new QProcess;

    connect(process, &QProcess::started, this, &Ping::onStarted);
    connect(process, &QProcess::stateChanged, this, &Ping::stateChanged);
    connect(process, &QProcess::readyRead, this, &Ping::readyRead);
    connect(process, &QProcess::readyReadStandardOutput, this, &Ping::readyReadStandardOutput);
    connect(process, &QProcess::errorOccurred, this, &Ping::errorOccurred);
    connect(process, &QProcess::readyReadStandardError, this, &Ping::readyReadStandardError);
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &Ping::onFinished);
}

void Ping::start()
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

void Ping::onStarted()
{
    qInfo() << Q_FUNC_INFO;
    emit started();
}

void Ping::stateChanged(QProcess::ProcessState newState)
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

void Ping::errorOccurred(QProcess::ProcessError error)
{
    if(listening == false) return;
    qInfo() << Q_FUNC_INFO;
    emit output("Error occurred");
}

void Ping::readyReadStandardError()
{
    if(listening == false) return;
    qInfo() << Q_FUNC_INFO;
    QByteArray stdErr = process->readAllStandardError();
    emit output(stdErr.trimmed());
}

void Ping::readyRead()
{
    if(listening == false) return;
    qInfo() << Q_FUNC_INFO;
    QByteArray result = process->readAll();
    emit output(result.trimmed());
}

void Ping::readyReadStandardOutput()
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
