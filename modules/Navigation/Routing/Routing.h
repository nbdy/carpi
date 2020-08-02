//
// Created by nbdy on 28.07.20.
//

#ifndef CARPI_QT_ROUTING_H
#define CARPI_QT_ROUTING_H

#include <QWidget>

#include <osmscout/OSMScoutQt.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Routing; }
QT_END_NAMESPACE

class Routing : public QWidget {
Q_OBJECT
private:
    Ui::Routing *ui;

private slots:
    void currentLocationButtonClicked();

public:
    explicit Routing(QWidget *parent = nullptr);
    ~Routing() override;
};


#endif //CARPI_QT_ROUTING_H
