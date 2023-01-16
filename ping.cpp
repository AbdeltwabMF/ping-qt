#include <QByteArray>

#include <QDebug>

#include "ping.h"

Ping::Ping(QObject *parent)
    : QObject{parent}
{
    process = new QProcess;

    connect(process, &QProcess::started, this, &Ping::started);
    connect(process, &QProcess::stateChanged, this, &Ping::stateChanged);
    connect(process, &QProcess::readyRead, this, &Ping::readyRead);
    connect(process, &QProcess::readyReadStandardOutput, this, &Ping::readyReadStandardOutput);
    connect(process, &QProcess::errorOccurred, this, &Ping::errorOccurred);
    connect(process, &QProcess::readyReadStandardError, this, &Ping::readyReadStandardError);
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &Ping::finished);
}

QString Ping::getProcessName() const
{
    if(QSysInfo::productType() == "windows") return "cmd";

    return "bash";
}

void Ping::startPing(const QString &address)
{
    QByteArray command;
    command.append("ping " + address.toStdString());

    if(QSysInfo::productType() == "windows") command.append("\r");
    command.append("\n");

    process->write("echo off\r\n");
    process->write("cls\r\n");

    process->write(command);
}

void Ping::start()
{
    qInfo() << Q_FUNC_INFO;
    process->start(getProcessName());
}

void Ping::stop()
{
    qInfo() << Q_FUNC_INFO;
    process->close();
}

void Ping::started()
{
    qInfo() << Q_FUNC_INFO;
}

void Ping::stateChanged(QProcess::ProcessState newState)
{
    qInfo() << Q_FUNC_INFO;
    switch(newState)
    {
        case QProcess::NotRunning:
            emit output("Not running");
        break;
        case QProcess::Starting:
            emit output("Starting");
        break;
        case QProcess::Running:
            emit output("Running");
            startPing(address + " " + args);
        break;
    }
}

void Ping::errorOccurred(QProcess::ProcessError error)
{
    qInfo() << Q_FUNC_INFO;
    emit output("Error occurred");
}

void Ping::readyReadStandardError()
{
    qInfo() << Q_FUNC_INFO;
    QByteArray stdErr = process->readAllStandardError();
    emit output(stdErr.trimmed());
}

void Ping::readyRead()
{
    qInfo() << Q_FUNC_INFO;
    QByteArray result = process->readAll();
    emit output(result.trimmed());
}

void Ping::readyReadStandardOutput()
{
    qInfo() << Q_FUNC_INFO;
    QByteArray stdOut = process->readAllStandardOutput();
    emit output(stdOut.trimmed());
}

void Ping::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qInfo() << Q_FUNC_INFO;
    Q_UNUSED(exitCode);
    Q_UNUSED(exitStatus);
    emit output("Complete");
}

bool Ping::isRunning()
{
    return (process->state() == QProcess::Running);
}
