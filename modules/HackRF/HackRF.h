#ifndef CARPI_QT_HACKRF_H
#define CARPI_QT_HACKRF_H

#include "HackRF_global.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class HackRF; }
QT_END_NAMESPACE

class HackRF : public QMainWindow
{
Q_OBJECT
private:
    Ui::HackRF *ui;

public:
    explicit HackRF(QWidget *parent = nullptr);
    ~HackRF() override;
};

extern "C" {
    HACKRF_EXPORT char* getName();
    HACKRF_EXPORT QWidget* render();
};


#endif //CARPI_QT_HACKRF_H
