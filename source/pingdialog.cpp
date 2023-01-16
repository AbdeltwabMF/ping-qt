#include <QtWidgets>
#include <QSizePolicy>

#include "../include/pingdialog.h"

PingDialog::PingDialog(QWidget *parent)
    : QDialog(parent)
{
    qDebug() << this->size();

    QFontDatabase::addApplicationFont(":/fonts/Quicksand-Regular.ttf");
    QFont font = QFont("Quicksand", 13, 500);
    setFont(font);

    pingProcess = new Ping;

    osName = new QLabel;
    osName->setText("OS: " + QSysInfo::prettyProductName());
    osName->setStyleSheet("QLabel {"
                          "background-color: #e3e3e3;"
                          "color: #3f3f3f;"
                          "padding: 4 0;"
                          "border: 1px solid #3f3f3f33;"
                          "border-radius: 8%;"
                          "font-weight: 700;"
                          "font-size: 16;"
                          "font-family: Quicksand;"
                          "};");
    osName->setAlignment(Qt::AlignCenter);

    addressLineLabel = new QLabel(tr("&Address:"));
    addressLine = new QLineEdit;
    addressLineLabel->setBuddy(addressLine);
    addressLine->setStyleSheet("QLineEdit {"
                               "border: 1px solid #939393;"
                               "font-weight: 600;"
                               "font-family: Quicksand;"
                               "font-size: 14;"
                               "padding: 3 3;"
                               "border-radius: 4%;"
                               "}"
                               "QLineEdit:hover:!pressed {"
                               "border: 1px solid #60CDCF;"
                               "}");

    startButton = new QPushButton(tr("&Start"));
    startButton->setDefault(true);
    startButton->setStyleSheet("QPushButton {"
                               "background-color: #9AFFC0;"
                               "color: #023314;"
                               "border-radius: 4%;"
                               "font-family: Quicksand;"
                               "font-weight: 500;"
                               "font-size: 14;"
                               "padding: 3 16;"
                               "border: 1px solid #019538;"
                               "}"
                               "QPushButton:hover:!pressed {"
                               "background-color: #5FEF94;"
                               "}");


    connect(startButton, &QPushButton::clicked, this, &PingDialog::startClicked);

    stopButton = new QPushButton(tr("&Stop"));
    stopButton->setDefault(true);
    stopButton->setStyleSheet("QPushButton {"
                              "background-color: #F99F9F;"
                              "color: #330202;"
                              "border-radius: 4%;"
                              "font-family: Quicksand;"
                              "font-size: 14;"
                              "font-weight: 500;"
                              "padding: 3 16;"
                              "border: 1px solid #B70404;"
                              "}"
                              "QPushButton:hover:!pressed {"
                              "background-color: #E08585;"
                              "}");


    connect(stopButton, &QPushButton::clicked, pingProcess, &Ping::stop);

    pingResult = new QTextEdit;
    pingResult->setReadOnly(true);
    pingResult->setStyleSheet("QTextEdit {"
                              "font-size: 9;"
                              "font-family: Quicksand;"
                              "}");

    connect(pingProcess, &Ping::output, this, &PingDialog::output);
    connect(pingProcess, &Ping::clear, pingResult, &QTextEdit::clear, Qt::QueuedConnection);

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
    setMinimumSize(890, 550);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);

    setWindowTitle(tr("Ping Qt"));
    setSizeGripEnabled(true);

    qDebug() << this->size();
}

PingDialog::~PingDialog()
{
}

void PingDialog::output(const QString &data)
{
    pingResult->append(data);
}

void PingDialog::startClicked()
{
    if (pingProcess->isRunning() == true)
        return;

    pingProcess->address = addressLine->text();
    pingProcess->args = "-t";
    pingProcess->start();
}

void PingDialog::clear()
{
    pingResult->clear();
}
