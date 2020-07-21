//
// Created by insane on 21.07.20.
//

#ifndef CARPI_QT_SETTINGSTAB_H
#define CARPI_QT_SETTINGSTAB_H

#include <QWidget>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class SettingsTab; }
QT_END_NAMESPACE

class SettingsTab : public QWidget {
Q_OBJECT
private:
    Ui::SettingsTab *ui;

public:
    explicit SettingsTab(QWidget *parent = nullptr);
    explicit SettingsTab(const QString& key, QWidget *parent = nullptr);
    ~SettingsTab() override;

};


#endif //CARPI_QT_SETTINGSTAB_H
