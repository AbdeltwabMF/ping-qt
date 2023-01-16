#include <QtWidgets>

#include "pingdialog.h"

PingDialog::PingDialog(QWidget *parent)
    : QDialog(parent)
{
    osName = new QLineEdit;
    osName->setText("OS: ");
    osName->setReadOnly(true);

    addressLineLabel = new QLabel(tr("&Address:"));
    addressLine = new QLineEdit;
    addressLineLabel->setBuddy(addressLine);

    startButton = new QPushButton(tr("&Start"));
    startButton->setDefault(true);

    connect(startButton, SIGNAL(clicked()), this, SLOT(startClicked()));

    stopButton = new QPushButton(tr("&Stop"));
    stopButton->setDefault(true);

    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopClicked()));

    output = new QLineEdit;
    output->setText("");
    output->setReadOnly(true);

    QFont font = output->font();
    font.setPointSize(font.pointSize() + 8);
    output->setFont(font);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(osName);

    QHBoxLayout *middleLayout = new QHBoxLayout;
    middleLayout->addWidget(addressLineLabel);
    middleLayout->addWidget(addressLine);
    middleLayout->addWidget(startButton);
    middleLayout->addWidget(stopButton);

    QVBoxLayout *bottomLayout = new QVBoxLayout;
    bottomLayout->addWidget(output);

    QGridLayout *mainLayout = new QGridLayout();

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(topLayout, 0, 1);
    mainLayout->addLayout(middleLayout, 1, 1);
    mainLayout->addLayout(bottomLayout, 2, 1);

    mainLayout->setRowStretch(3, 2);


    setLayout(mainLayout);

    setWindowTitle(tr("Ping"));
}

PingDialog::~PingDialog()
{
    delete addressLineLabel;
    delete addressLine;
    delete startButton;
    delete stopButton;
    delete output;
}

void PingDialog::startClicked()
{
    output->setText(addressLine->text());
}

void PingDialog::stopClicked()
{
    output->clear();
}
