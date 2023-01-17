#include <QtWidgets>
#include <QSizePolicy>

#include "../include/pingdialog.h"

PingDialog::PingDialog(QWidget *parent)
    : QDialog(parent)
{
    qDebug() << this->size();
    pingProcess = new Ping;

    connect(this, &QDialog::rejected, pingProcess, &Ping::stop);

    osName = new QLabel;
    osName->setText(QSysInfo::prettyProductName());
    osName->setStyleSheet("QLabel {"
                          "background-color: #e3e3e3;"
                          "color: #3f3f3f;"
                          "padding: 4 0;"
                          "border-radius: 8%;"
                          "};");
    osName->setAlignment(Qt::AlignCenter);

    addressLine = new QLineEdit;
    addressLine->setStyleSheet("QLineEdit {"
                               "background-color: #EBEBEB;"
                               "border: 2px solid #C3C3C3;"
                               "padding: 3 3;"
                               "border-radius: 4%;"
                               "}"
                               "QLineEdit:hover:!pressed {"
                               "border: 2px solid #60CDCF;"
                               "}"
                               "QLineEdit:focus, QLineEdit:hover {"
                               "background-color: #F9F9F9;"
                               "}");

    startButton = new QPushButton(tr("&Start"));
    startButton->setDefault(true);
    startButton->setStyleSheet("QPushButton {"
                               "background-color: #2CA542;"
                               "color: #ffffff;"
                               "border-radius: 8%;"
                               "border: 2px solid #018C1A;"
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
                              "border-radius: 8%;"
                              "border: 2px solid #BC2100;"
                              "padding: 6 32;"
                              "}"
                              "QPushButton:hover:!pressed {"
                              "background-color: #BC2100;"
                              "}");


    connect(stopButton, &QPushButton::clicked, pingProcess, &Ping::stop);

    pingResult = new QPlainTextEdit;
    pingResult->setPlainText("No output yet.");
    pingResult->setReadOnly(true);

    pingResult->setStyleSheet("QPlainTextEdit {"
                              "background-color: #f4f4f4;"
                              "color: #545454;"
                              "border-radius: 4%;"
                              "}");
    pingResult->setFixedHeight(280);
    pingResult->setFixedWidth(620);

    qInfo() << "QPlainTextEdit: " << pingResult->maximumWidth();
    qInfo() << "QPlainTextEdit: " << pingResult->maximumHeight();

    connect(pingProcess, &Ping::output, this, &PingDialog::output);

    QHBoxLayout *osLayout = new QHBoxLayout;
    osLayout->addWidget(osName);

    QGroupBox *osGroup = new QGroupBox(tr("&Operating System"));
    osGroup->setLayout(osLayout);

    QHBoxLayout *addressLayout = new QHBoxLayout;
    addressLayout->addWidget(addressLine);

    QGroupBox *addressGroup = new QGroupBox(tr("&Address"));
    addressGroup->setLayout(addressLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(stopButton);

    QVBoxLayout *outputLayout = new QVBoxLayout;
    outputLayout->addWidget(pingResult);

    QGroupBox *outputGroup = new QGroupBox(tr("&Output"));
    outputGroup->setLayout(outputLayout);

    QGridLayout *mainLayout = new QGridLayout();

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(osGroup, 0, 1);
    mainLayout->addWidget(addressGroup, 1, 1);
    mainLayout->addWidget(outputGroup, 2, 1);
    mainLayout->addLayout(buttonLayout, 3, 1);

    mainLayout->setRowStretch(4, 2);

    setLayout(mainLayout);

    setSizeGripEnabled(true);
    setWindowIcon(QIcon(":/images/icon.png"));
    setWindowTitle(tr("Ping Qt"));
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
