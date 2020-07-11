//
// Created by nbdy on 11.06.20.
//

#include "View.h"

void View::_overrideCatchAll() {
    std::cout << "this should be overwritten" << std::endl;
}

View::View(const std::string &name, const std::string &parent) {
    this->name = name;
    this->parent = parent;
    this->keyboard = new KeyboardLayout();
}

View::View(const std::string &name, const std::string &parent, KeyboardLayout *keyboard) {
    name = "settings audio";
    parent = "settings";
    this->keyboard = keyboard;
}

std::vector<Toast *> View::getToasts() {
    std::vector<Toast*> r = std::move(toasts);
    toasts.clear();
    return r;
}

void View::processKeyboard() {
    std::string keyboardData;
    if(showKeyboard) keyboardData = keyboard->draw();
    if(KeyHide::isPressed(keyboardData)) showKeyboard = false;
    else keyboardBuffer += keyboardData;
}

void View::setName(const std::string &_name) {
    this->name = _name;
}

std::string View::getParent() {
    return parent;
}

View::View() {

}

void View::setParent(const std::string &_name) {
    this->parent = name;
}

std::string View::getName() {
    return name;
}

std::string View::getNextView() {
    return std::string();
}

void View::setValuesFalse() {

}

void View::_drawBaseUI() {
    runningInBackground = GuiCheckBox((Rectangle){84, 550, 42, 42}, "shortcut", runningInBackground);
    openWidget = GuiCheckBox((Rectangle){242, 550, 42, 42}, "widget", openWidget);
}

void View::addToast(Toast *toast) {
    toasts.emplace_back(toast);
}

std::string View::getSettings() {
    return "settings " + name;
}

void View::show(Manager *mgr) {
    _overrideCatchAll();
}

void View::setKeyboard(KeyboardLayout* kb) {
    keyboard = kb;
}

void View::setKeyboardBuffer(const std::string &data) {
    keyboardBuffer = data;
}

std::string View::getKeyboardBuffer() {
    return keyboardBuffer;
}
