//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWWITHBACK_H
#define CARPI_VIEWWITHBACK_H

#include <string>
#include <vector>
#include "../View.h"

class ViewWithBack : public View {
protected:
    bool viewBackSelected = false;
    std::vector<std::string> viewsInBackground = {};
    std::string selectedBackgroundView;

public:
    ViewWithBack();
    void drawBackButton();
    std::string getNextView() override;
    void setValuesFalse() override;
    std::string getSelectedBackgroundView();
    void setViewsInBackground(std::vector<std::string> views);
    void addViewInBackground(const std::string& view);
    void removeViewInBackground(const std::string& view);
};


#endif //CARPI_VIEWWITHBACK_H
