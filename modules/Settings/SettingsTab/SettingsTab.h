//
// Created by insane on 21.07.20.
//

#ifndef CARPI_QT_SETTINGSTAB_H
#define CARPI_QT_SETTINGSTAB_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QGridLayout>
#include <QTextEdit>
#include <QCheckBox>
#include "../../../libs/ISettings/ISettings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SettingsTab; }
QT_END_NAMESPACE

class SettingsTab : public QWidget {
Q_OBJECT
private:
    const QString& groupKey;
    Ui::SettingsTab *ui;
    QGridLayout *layout;
    QSettings *settings;

    void populateKeyValues();
    QWidget *createAccordingWidget(const QString& key, const QVariant& value);

    template<typename T> void setKeyValue(const QString& key, T value);

public:
    explicit SettingsTab(const QString& key, QWidget *parent = nullptr);
    ~SettingsTab() override;
};


#endif //CARPI_QT_SETTINGSTAB_H
