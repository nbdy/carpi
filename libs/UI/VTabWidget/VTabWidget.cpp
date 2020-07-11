//
// Created by insane on 11.07.20.
//

#include "VTabWidget.h"
#include "../VTabBar/VTabBar.h"

void VTabWidget::_setStyleSheet()
{
    std::string ss = "QTabBar::tab { height: ";
    ss += std::to_string(tabHeight);
    ss += "px; width: ";
    ss += std::to_string(tabWidth);
    ss += "px; }";
    setStyleSheet(ss.c_str());
}

VTabWidget::VTabWidget()
{
    setTabBar(new VTabBar());
    setTabPosition(QTabWidget::West);
    _setStyleSheet();
}

VTabWidget::VTabWidget(int tabHeight, int tabWidth){
    this->tabHeight = tabHeight;
    this->tabWidth = tabWidth;
    _setStyleSheet();
}