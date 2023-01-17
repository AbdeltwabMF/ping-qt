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
    QPushButton *startButton;
    QPushButton *stopButton;
    QPlainTextEdit *pingResult;
    Ping *pingProcess;

private slots:
    void output(const QString &data);
    void startClicked();
};

#endif // MAINWINDOW_H
