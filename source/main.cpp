#include <QApplication>

#include "../include/pingdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PingDialog dialog;
    dialog.show();

    return app.exec();
}
