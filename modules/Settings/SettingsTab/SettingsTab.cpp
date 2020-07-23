//
// Created by insane on 21.07.20.
//

#include "SettingsTab.h"
#include "ui_settingstab.h"

SettingsTab::SettingsTab(const QString &key, QWidget *parent): QWidget(parent), ui(new Ui::SettingsTab), groupKey(key) {
    ui->setupUi(parent);
    settings = ISettings::getSettings(this);
    layout = new QGridLayout(this);
    populateKeyValues();
}

SettingsTab::~SettingsTab() {
    settings->sync();
    delete settings;
    delete layout;
    delete ui;
}

void SettingsTab::populateKeyValues() {
    int r = 0;
    settings->beginGroup(groupKey);
    for(const QString& k : settings->childKeys()){
        const auto& v = settings->value(k);
        auto *w = createAccordingWidget(k, v);
        if(w) {
            layout->addWidget(w, r, 0);
            r++;
        }
    }
    settings->endGroup();
}

QWidget *SettingsTab::createAccordingWidget(const QString &k, const QVariant &v) {
    qDebug() << "\t" << k << ":" << v;
    if(ISettings::getProbableType(v) == QMetaType::Bool){
        qDebug() << "\t\t" << "creating QCheckBox";
        auto *cb = new QCheckBox(k, this);
        cb->setStyleSheet("QCheckBox {color: rgb(115, 210, 22);background: none;font: 24px;}QCheckBox::indicator {width: 24px;height: 24px;}");
        cb->setChecked(v.toBool());
        connect(cb, &QCheckBox::stateChanged, this, [=](){setKeyValue(k, cb->isChecked());});
        return cb;
    } else if(ISettings::getProbableType(v) == QMetaType::QString) {
        qDebug() << "\t\t" << "creating QTextEdit";
        auto *et = new QTextEdit(k, this);
        // et->setStyleSheet(); todo
        et->setText(v.toString());
        connect(et, &QTextEdit::textChanged, this, [=](){setKeyValue(k, et->toPlainText());});
        return et;
    } // todo  int
    return nullptr;
}

template<typename T>
void SettingsTab::setKeyValue(const QString &key, T value) {
    settings->beginGroup(groupKey);
    settings->setValue(key, value);
    settings->endGroup();
}


