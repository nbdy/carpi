//
// Created by insane on 11.07.20.
//

#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "../../Utils/Utils.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

