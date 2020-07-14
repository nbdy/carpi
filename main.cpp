#include <iostream>

#include "libs/Manager/Manager.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    auto *manager = new Manager();
    int r = QApplication::exec();
    delete manager;
    return r;
}