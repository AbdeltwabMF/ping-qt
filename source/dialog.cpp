#include <QtWidgets>
#include <QSizePolicy>

#include "../include/dialog.h"

PingDialog::PingDialog(QWidget *parent)
    : QDialog(parent)
{
    qDebug() << this->size();
    pingProcess = new Ping;
    isRunning = false;

    connect(this, &QDialog::rejected, pingProcess, &Ping::stop);
    connect(this, &PingDialog::startClicked, pingProcess, &Ping::start);
    connect(this, &PingDialog::stopClicked, pingProcess, &Ping::stop);

    osName = new QLabel;
    QString systemIcon;
    if(QSysInfo::productType() == "windows")
    {
        systemIcon = "";
    } else if(QSysInfo::productType() == "macos") {
        systemIcon = "";
    } else {
        systemIcon = "";
    }

    osName->setText(systemIcon + "  " + QSysInfo::prettyProductName());
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

    button = new QPushButton(tr("&  Start"));
    button->setDefault(true);
    button->setStyleSheet("QPushButton {"
                          "background-color: #018C1A;"
                          "color: #ffffff;"
                          "border-radius: 8%;"
                          "padding: 8 32;"
                          "}"
                          "QPushButton:hover:!pressed {"
                          "background-color: #2CA542;"
                          "}");

    connect(button, &QPushButton::clicked, this, &PingDialog::onButtonClicked);
    connect(pingProcess, &Ping::started, this, &PingDialog::onStarted);
    connect(pingProcess, &Ping::finished, this, &PingDialog::onFinished);

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
    buttonLayout->addWidget(button);

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
    setWindowTitle(tr("Ping"));
    setWindowFlags(
        Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
}

PingDialog::~PingDialog()
{
}

void PingDialog::output(const QString &data)
{
    pingResult->appendPlainText(data);
}

void PingDialog::onButtonClicked()
{
    if(isRunning == true) {
        emit stopClicked();
    } else {
        emit startClicked(addressLine->text(), "-t");
    }
}

void PingDialog::onStarted()
{
    pingResult->clear();
    isRunning = true;
    button->setText(tr("&  Stop"));

    button->setStyleSheet("QPushButton {"
                          "background-color: #BC2100;"
                          "color: #ffffff;"
                          "border-radius: 8%;"
                          "padding: 8 32;"
                          "}"
                          "QPushButton:hover:!pressed {"
                          "background-color: #DA4D2E;"
                          "}");
}

void PingDialog::onFinished()
{
    isRunning = false;
    button->setText(tr("&  Start"));

    button->setStyleSheet("QPushButton {"
                          "background-color: #018C1A;"
                          "color: #ffffff;"
                          "border-radius: 8%;"
                          "padding: 8 32;"
                          "}"
                          "QPushButton:hover:!pressed {"
                          "background-color: #2CA542;"
                          "}");
}
