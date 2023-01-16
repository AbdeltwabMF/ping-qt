#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

#include "ping.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QPushButton;
class QPlainTextEdit;
class QTextEdit;
QT_END_NAMESPACE

class PingDialog : public QDialog
{
    Q_OBJECT
public:
    PingDialog(QWidget *parent = nullptr);
    ~PingDialog();

private:
    QLineEdit *osName;

    QLabel *addressLineLabel;
    QLineEdit *addressLine;

    QPushButton *startButton;
    QPushButton *stopButton;

    QTextEdit *pingResult;

    Ping *pingProcess;

private slots:
    void output(const QString &data);
    void clear();
    void startClicked();
};

#endif // MAINWINDOW_H
