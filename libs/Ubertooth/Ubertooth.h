//
// Created by insane on 01.05.19.
//

#ifndef CARPI_UBERTOOTH_H
#define CARPI_UBERTOOTH_H

#include <btbb.h>
#include <ubertooth.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/hci.h>
#include "../Utils/Utils.h"

class Ubertooth {
public:
    Ubertooth();
    ~Ubertooth();

    int jam(uint32_t lap, uint32_t uap);

private:
    ubertooth_t *ut;
};


#endif //CARPI_UBERTOOTH_H
