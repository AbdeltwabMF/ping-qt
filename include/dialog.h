#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

#include "ping.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QPushButton;
class QPlainTextEdit;
QT_END_NAMESPACE

class PingDialog : public QDialog
{
    Q_OBJECT
public:
    PingDialog(QWidget *parent = nullptr);
    ~PingDialog();

private:
    QLabel *osName;
    QLineEdit *addressLine;
    Ping *pingProcess;
    QPlainTextEdit *pingResult;
    QPushButton *button;
    bool isRunning;

signals:
    void startClicked(const QString &address, const QString &args);
    void stopClicked();

private slots:
    void output(const QString &data);
    void onStarted();
    void onFinished();
    void onButtonClicked();
};

#endif // MAINWINDOW_H
