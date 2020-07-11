//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_MAINWINDOW_H
#define CARPI_QT_MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT
private:
    Ui::MainWindow *ui;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};


#endif //CARPI_QT_MAINWINDOW_H
