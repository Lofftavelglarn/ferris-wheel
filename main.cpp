#include <QApplication>
#include "ferriswheel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    FerrisWheel window;
    window.show();
    return app.exec();
}
