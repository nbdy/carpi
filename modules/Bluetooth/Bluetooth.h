
#ifndef CARPI_QT_BLUETOOTH_H
#define CARPI_QT_BLUETOOTH_H

#include "Bluetooth_global.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Bluetooth; }
QT_END_NAMESPACE

class Bluetooth : public QMainWindow
{
Q_OBJECT
private:
    Ui::Bluetooth *ui;

public:
    explicit Bluetooth(QWidget *parent = nullptr);
    ~Bluetooth() override;
};

extern "C" {
    BLUETOOTH_EXPORT QString getName();
    BLUETOOTH_EXPORT QWidget* render();
};


#endif //CARPI_QT_BLUETOOTH_H
