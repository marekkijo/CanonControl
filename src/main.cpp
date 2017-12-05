#include <memory>

#include <QtWidgets/QApplication>

#include "canoncontrol.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    auto w_ptr{std::make_shared<CanonControl>()};

    if (!w_ptr->init()) {
      return 1;
    }

    w_ptr->show();

    return a.exec();
}
