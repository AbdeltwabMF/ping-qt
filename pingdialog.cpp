#include <QtWidgets>

#include "pingdialog.h"

PingDialog::PingDialog(QWidget *parent)
    : QDialog(parent)
{
    pingProcess = new Ping;

    osName = new QLineEdit;
    osName->setText("OS: " + QSysInfo::prettyProductName());
    osName->setReadOnly(true);

    addressLineLabel = new QLabel(tr("&Address:"));
    addressLine = new QLineEdit;
    addressLineLabel->setBuddy(addressLine);

    startButton = new QPushButton(tr("&Start"));
    startButton->setDefault(true);

    connect(startButton, &QPushButton::clicked, this, &PingDialog::startClicked);

    stopButton = new QPushButton(tr("&Stop"));
    stopButton->setDefault(true);

    connect(stopButton, &QPushButton::clicked, pingProcess, &Ping::stop);

    pingResult = new QPlainTextEdit;
    pingResult->appendPlainText("");
    pingResult->setReadOnly(true);

    connect(pingProcess, &Ping::output, this, &PingDialog::output);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(osName);

    QHBoxLayout *middleLayout = new QHBoxLayout;
    middleLayout->addWidget(addressLineLabel);
    middleLayout->addWidget(addressLine);
    middleLayout->addWidget(startButton);
    middleLayout->addWidget(stopButton);

    QVBoxLayout *bottomLayout = new QVBoxLayout;
    bottomLayout->addWidget(pingResult);

    QGridLayout *mainLayout = new QGridLayout();

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(topLayout, 0, 1);
    mainLayout->addLayout(middleLayout, 1, 1);
    mainLayout->addLayout(bottomLayout, 2, 1);

    mainLayout->setRowStretch(3, 2);


    setLayout(mainLayout);

    setWindowTitle(tr("Ping Qt"));
    setSizeGripEnabled(true);
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
    if(pingProcess->isRunning() == true) return;

    pingProcess->address = addressLine->text();
    pingProcess->args = "-t";
    pingProcess->start();
}
