#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connectorwidget.h"
#include <QMessageBox>
#include <config.h>
#include <defines.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void combo_second_cahange();
    void combo_first_cahange();
    void onComboBoxRightActivated();
    ~MainWindow();

public slots:
    void fillCombos();

private slots:

    void on_pushButton_reset_clicked();

    void on_actionNew_triggered();


    void on_pushButton_update_clicked();

private:
    Ui::MainWindow *ui;

    ConnectorWidget *Connector;  // rectangle widget

    config *configObj;



};
#endif // MAINWINDOW_H
