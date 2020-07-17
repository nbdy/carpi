#ifndef CARPI_QT_WIFI_H
#define CARPI_QT_WIFI_H

#include "WiFi_global.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class WiFi; }
QT_END_NAMESPACE

class WiFi : public QWidget
{
Q_OBJECT
private:
    Ui::WiFi *ui;

public:
    explicit WiFi(QWidget *parent = nullptr);
    ~WiFi() override;
};

extern "C" {
    WIFI_EXPORT int getDefaultIndex();
    WIFI_EXPORT char* getName();
    WIFI_EXPORT QWidget* render();
};


#endif //CARPI_QT_WIFI_H
