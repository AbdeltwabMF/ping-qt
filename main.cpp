#include <QApplication>

#include "pingdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PingDialog dialog;
    dialog.adjustSize();
    dialog.show();

    return app.exec();
}
