#include "canoncontrol.hpp"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CanonControl w;
    w.show();
    return a.exec();
}
