//
// Created by nbdy on 11.06.20.
//

#ifndef CARPI_TOASTMANAGER_H
#define CARPI_TOASTMANAGER_H

#include <vector>
#include "../Toast/Toast.h"

class ToastManager {
private:
    std::vector<Toast*> toasts;

public:
    ToastManager(){}

    void addToasts(std::vector<Toast*> toasts){
        for(Toast *t : toasts) this->toasts.emplace_back(t);
    }

    void loop(){
        for(unsigned long p = 0; p < toasts.size(); p++) {
            if (!toasts.at(p)->show()) toasts.erase(toasts.begin() + p);
        }
    }
};


#endif //CARPI_TOASTMANAGER_H
