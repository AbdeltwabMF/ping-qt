#include <QApplication>
#include <QMainWindow>
#include <QFontDatabase>

#include "../include/pingdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/FantasqueSansMono.ttf");
    app.setFont(QFont("FantasqueSansMono Nerd Font", 14));

    PingDialog dialog;
    dialog.show();

    return app.exec();
}
