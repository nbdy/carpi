//
// Created by insane on 21.07.20.
//

#include "SettingsTab.h"
#include "ui_settingstab.h"

SettingsTab::SettingsTab(const QString &key, QWidget *parent): QWidget(parent), ui(new Ui::SettingsTab) {
    ui->setupUi(parent);
    settings = ISettings::getSettings(this);
    settings->beginGroup(key);
    layout = new QGridLayout(this);
    populateKeyValues();
}

SettingsTab::~SettingsTab() {
    settings->endGroup();
    settings->sync();
    delete settings;
    delete layout;
    delete ui;
}

void SettingsTab::populateKeyValues() {
    int r = 0;
    for(const QString& k : settings->childKeys()){
        const auto& v = settings->value(k);
        auto *w = createAccordingWidget(k, v);
        if(w) {
            layout->addWidget(w, r, 0);
            r++;
        }
    }
}

QWidget *SettingsTab::createAccordingWidget(const QString &k, const QVariant &v) {
    qDebug() << "\t" << k << ":" << v;
    if(ISettings::getProbableType(v) == QMetaType::Bool){
        qDebug() << "\t\t" << "creating QCheckBox";
        auto *cb = new QCheckBox(k, this);
        cb->setStyleSheet("QCheckBox {color: rgb(115, 210, 22);background: none;font: 24px;}QCheckBox::indicator {width: 24px;height: 24px;}");
        cb->setChecked(v.toBool());
        return cb;
    } else if(ISettings::getProbableType(v) == QMetaType::QString) {
        qDebug() << "\t\t" << "creating QTextEdit";
        auto *et = new QTextEdit(k, this);
        // et->setStyleSheet(); todo
        et->setText(v.toString());
        return et;
    } // todo  int
    return nullptr;
}


