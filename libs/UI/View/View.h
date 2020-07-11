//
// Created by nbdy on 11.06.20.
//

#ifndef CARPI_VIEW_H
#define CARPI_VIEW_H

#include <string>
#include <vector>
#include <iostream>
#include "../Toast/Toast.h"
#include "../Keyboard/Layout/KeyboardLayout.h"
#include "../../Manager/Manager.h"
#include "../../MusicLibrary/MusicLibrary.h"

class View {
private:
    std::string name;
    std::string parent;

    std::vector<Toast*> toasts;

    KeyboardLayout* keyboard;
    std::string keyboardBuffer;

protected:
    bool showKeyboard = false;

    void _overrideCatchAll();

public:
    void setName(const std::string& name);
    void setParent(const std::string& name);
    std::string getParent();
    std::string getName();
    void setKeyboard(KeyboardLayout* kb);
    void setKeyboardBuffer(const std::string& data);
    std::string getKeyboardBuffer();

    bool openWidget = false;
    bool runningInBackground = false;

    View();
    explicit View(const std::string& name, const std::string& parent);
    explicit View(const std::string& name, const std::string& parent, KeyboardLayout* keyboard);

    virtual void show(Manager* mgr);
    std::string getSettings();
    void addToast(Toast* toast);
    void _drawBaseUI();

    virtual std::string getNextView();
    virtual void setValuesFalse();

    std::vector<Toast*> getToasts();
    void processKeyboard();
};

#endif //CARPI_VIEW_H
