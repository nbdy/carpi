#ifndef CARPI_QT_BLUETOOTH_H
#define CARPI_QT_BLUETOOTH_H

#include "Bluetooth_global.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Bluetooth; }
QT_END_NAMESPACE

class Bluetooth : public QWidget
{
Q_OBJECT
private:
    Ui::Bluetooth *ui;

public:
    explicit Bluetooth(QWidget *parent = nullptr);
    ~Bluetooth() override;
};

extern "C" {
    BLUETOOTH_EXPORT int getDefaultIndex();
    BLUETOOTH_EXPORT char* getName();
    BLUETOOTH_EXPORT QWidget* render();
};


#endif //CARPI_QT_BLUETOOTH_H
