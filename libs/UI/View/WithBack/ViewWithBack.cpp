//
// Created by insane on 14.06.20.
//

#include "ViewWithBack.h"

ViewWithBack::ViewWithBack() {
    setName("back");
    setParent("");
}

void ViewWithBack::drawBackButton() {
    viewBackSelected = GuiButton((Rectangle) {592, 492, 200, 100}, "back");
    float x = 492;
    float y = 392;
    for(const std::string& v : viewsInBackground) {
        bool s = GuiButton((Rectangle) {x, y, 200, 100}, v.c_str());
        if(s) selectedBackgroundView = v;
        x -= 200;
        y -= 100;
    }
}

std::string ViewWithBack::getNextView() {
    if(viewBackSelected) return getParent();
    else return getName();
}

void ViewWithBack::setValuesFalse() {
    viewBackSelected = false;
    selectedBackgroundView = "";
}

std::string ViewWithBack::getSelectedBackgroundView() {
    return selectedBackgroundView;
}

void ViewWithBack::setViewsInBackground(std::vector<std::string> views) {
    viewsInBackground = std::move(views);
}

void ViewWithBack::addViewInBackground(const std::string& view) {
    viewsInBackground.emplace_back(view);
}

void ViewWithBack::removeViewInBackground(const std::string &view) {
    viewsInBackground = Utils::removeFromVector(viewsInBackground, view);
}
