//
// Created by insane on 01.05.19.
//

#include "Ubertooth.h"


Ubertooth::Ubertooth() {
    ut = ubertooth_init();
}

Ubertooth::~Ubertooth() {
    ubertooth_stop(ut);
}

int Ubertooth::jam(uint32_t lap, uint32_t uap) {
    int dev_id;
    uint16_t accuracy, handle;
    uint32_t clock;
    if(Utils::isPi()) dev_id = hci_devid("hci1");
    else dev_id = hci_devid("hci0");
    int sock = hci_open_dev(dev_id);
    hci_read_clock(sock, 0, 0, &clock, &accuracy, 0);
    char addr[19] = { 0 };
    bdaddr_t bdaddr;
    btbb_piconet *pn = btbb_piconet_new();
    btbb_init_piconet(pn, lap);
    btbb_piconet_set_uap(pn, uap);
    sprintf(addr, "00:00:%02X:%02X:%02X:%02X",
            uap,
            (lap >> 16) & 0xFF,
            (lap >> 8) & 0xFF,
            lap & 0xFF
    );
    str2ba(addr, &bdaddr);
    struct hci_dev_info di;
    if (hci_devinfo(dev_id, &di) < 0) {
        perror("[ubertooth] can't get device info");
        return 1;
    }
    if (hci_create_connection(sock, &bdaddr,
                              htobs(di.pkt_type & ACL_PTYPE_MASK),
                              0, 0x01, &handle, 25000) < 0) {
        perror("Can't create connection");
        return 1;
    }
    // todo send data to remote host / on channel
}