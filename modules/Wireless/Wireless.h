#ifndef CARPI_QT_WIRELESS_H
#define CARPI_QT_WIRELESS_H

#include "Wireless_global.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Wireless; }
QT_END_NAMESPACE

class Wireless : public QWidget
{
Q_OBJECT
private:
    Ui::Wireless *ui;

public:
    explicit Wireless(QWidget *parent = nullptr);
    ~Wireless() override;
};

extern "C" {
    WIRELESS_EXPORT char* getName();
    WIRELESS_EXPORT QWidget* render();
};


#endif //CARPI_QT_WIRELESS_H
