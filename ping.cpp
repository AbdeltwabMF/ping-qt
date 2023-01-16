#include "ping.h"

Ping::Ping(QObject *parent)
    : QObject{parent}
{

}

void Ping::startProcess(QString &address)
{
    process = new QProcess();
    QString processName;

    if(QSysInfo::productType() == "windows")
    {
        processName = "C:\\WINDOWS\\system32\\ping.exe";
    } else {
        processName = "/usr/bin/ping";
    }

    process->start(processName);
}

QString Ping::getProcess()
{
    if(QSysInfo::productType() == "windows")
    {
        return "cmd";
    } else {
        return "bash";
    }
}
