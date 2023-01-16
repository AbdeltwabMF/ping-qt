#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QPushButton;
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

    QLineEdit *output;

private slots:
    void startClicked();
    void stopClicked();
};
#endif // MAINWINDOW_H
