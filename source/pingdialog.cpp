#include <QtWidgets>
#include <QSizePolicy>

#include "../include/pingdialog.h"

PingDialog::PingDialog(QWidget *parent)
    : QDialog(parent)
{
    qDebug() << this->size();
    pingProcess = new Ping;

    osName = new QLabel;
    osName->setText("OS: " + QSysInfo::prettyProductName());
    osName->setStyleSheet("QLabel {"
                          "background-color: #e3e3e3;"
                          "color: #3f3f3f;"
                          "padding: 4 0;"
                          "border: 1px solid #3f3f3f33;"
                          "border-radius: 8%;"
                          "};");
    osName->setAlignment(Qt::AlignCenter);

    addressLineLabel = new QLabel(tr("&Address:"));
    addressLine = new QLineEdit;
    addressLineLabel->setBuddy(addressLine);
    addressLine->setStyleSheet("QLineEdit {"
                               "background-color: #EBEBEB;"
                               "border: 1px solid #939393;"
                               "padding: 3 3;"
                               "border-radius: 4%;"
                               "}"
                               "QLineEdit:hover:!pressed {"
                               "border: 1px solid #60CDCF;"
                               "}"
                               "QLineEdit:focus, QLineEdit:hover {"
                               "background-color: #F9F9F9;"
                               "}");

    startButton = new QPushButton(tr("&Start"));
    startButton->setDefault(true);
    startButton->setStyleSheet("QPushButton {"
                               "background-color: #2CA542;"
                               "color: #ffffff;"
                               "border-radius: 4%;"
                               "padding: 6 32;"
                               "}"
                               "QPushButton:hover:!pressed {"
                               "background-color: #018C1A;"
                               "}");


    connect(startButton, &QPushButton::clicked, this, &PingDialog::startClicked);

    stopButton = new QPushButton(tr("&Stop"));
    stopButton->setDefault(true);
    stopButton->setStyleSheet("QPushButton {"
                              "background-color: #DA4D2E;"
                              "color: #ffffff;"
                              "border-radius: 4%;"
                              "padding: 6 32;"
                              "}"
                              "QPushButton:hover:!pressed {"
                              "background-color: #BC2100;"
                              "}");


    connect(stopButton, &QPushButton::clicked, pingProcess, &Ping::stop);

    pingResult = new QPlainTextEdit;
    pingResult->setReadOnly(true);

    pingResult->setStyleSheet("QPlainTextEdit {"
                              "background-color: #f4f4f4;"
                              "color: #545454;"
                              "border-radius: 4%;"
                              "border: 1px solid #DCA3FF;"
                              "padding: 8;"
                              "}");
    pingResult->setFixedHeight(350);
    pingResult->setFixedWidth(620);

    qInfo() << pingResult->maximumWidth();
    qInfo() << pingResult->maximumHeight();

    connect(pingProcess, &Ping::output, this, &PingDialog::output);

    QHBoxLayout *osLayout = new QHBoxLayout;
    osLayout->addWidget(osName);

    QHBoxLayout *addressLayout = new QHBoxLayout;
    addressLayout->addWidget(addressLineLabel);
    addressLayout->addWidget(addressLine);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(stopButton);

    QVBoxLayout *resultLayout = new QVBoxLayout;
    resultLayout->addWidget(pingResult);

    QGridLayout *mainLayout = new QGridLayout();

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(osLayout, 0, 1);
    mainLayout->addLayout(addressLayout, 1, 1);
    mainLayout->addLayout(buttonLayout, 2, 1);
    mainLayout->addLayout(resultLayout, 3, 1);

    mainLayout->setRowStretch(4, 2);

    setLayout(mainLayout);

    setWindowTitle(tr("Ping Qt"));
    setSizeGripEnabled(true);

    qDebug() << this->size();
}

PingDialog::~PingDialog()
{
}

void PingDialog::output(const QString &data)
{
    pingResult->appendPlainText(data);
}

void PingDialog::startClicked()
{
    if (pingProcess->isRunning() == true)
        return;

    pingResult->clear();

    pingProcess->address = addressLine->text();
    pingProcess->args = "-t";
    pingProcess->start();
}
