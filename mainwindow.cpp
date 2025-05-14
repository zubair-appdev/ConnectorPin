#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <config.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Connector");

    Connector = new ConnectorWidget(this);

    QVBoxLayout *FrameLayout = new QVBoxLayout(ui->frame);  // Use the existing Frame

    FrameLayout->addWidget(Connector);

    // Set the layout for the frame
    ui->frame->setLayout(FrameLayout);

    // Fill both combo boxes with select at application opening
    ui->comboBox_left->addItem("Select");
    ui->comboBox_right->addItem("Select");


    connect(ui->comboBox_right, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::combo_second_cahange);
    connect(ui->comboBox_left, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::combo_first_cahange);
    connect(ui->comboBox_right, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::onComboBoxRightActivated);



}

MainWindow::~MainWindow()
{
    delete ui;
    delete configObj;
    delete Connector;
}

void MainWindow::combo_second_cahange()
{

    flag = true;
    first_combo = ui->comboBox_left->currentText();
    second_combo = ui->comboBox_right->currentText();
    Connector->update();

    // Find the index of the item in comboBox_left that matches second_combo
    int indexToDisable = ui->comboBox_left->currentIndex();
    int indexToDisable2 = ui->comboBox_right->currentIndex();


    // Disable the matched item in comboBox_left
    if (indexToDisable != -1) { // Check if the item is found
        ui->comboBox_left->setItemData(indexToDisable, QVariant::fromValue(false), Qt::UserRole - 1);
        ui->comboBox_left->setCurrentIndex(0);

    }
    if (indexToDisable2 != -1) { // Check if the item is found
        ui->comboBox_right->setItemData(indexToDisable2, QVariant::fromValue(false), Qt::UserRole - 1);
    }

    if(ui->comboBox_left->currentText() == "Select")
    {
        qDebug()<<"is this 1";
        ui->comboBox_right->setEnabled(false);
    }

}
void MainWindow::combo_first_cahange()
{
    ui->comboBox_right->setEnabled(true);
}

void MainWindow::onComboBoxRightActivated()
{
    if(ui->comboBox_right->currentText() == "Select")
    {
        qDebug()<<"is this 2";
        QMessageBox::critical(this,"Warning","Invalid Selection");
    }
}


void MainWindow::on_pushButton_reset_clicked()
{
    flag = false;

    for (int i = 1; i < totalPins; ++i) {
        ui->comboBox_left->setItemData(i, QVariant(), Qt::UserRole - 1);
        ui->comboBox_right->setItemData(i, QVariant(), Qt::UserRole - 1);
    }
    ui->comboBox_right->setEnabled(true);
    ui->comboBox_left->setEnabled(true);

    ui->comboBox_left->setCurrentIndex(0);
    ui->comboBox_right->setCurrentIndex(0);

    Connector->drawnLines.clear();
    Connector->update();
}

void MainWindow::on_actionNew_triggered()
{
    configObj = new config(this);
    configObj->setModal(false);
    configObj->show();
}

void MainWindow::fillCombos()
{
    qDebug()<<"Is it calling fillCombos"<<totalPins;
    ui->comboBox_left->clear();
    ui->comboBox_right->clear();
    ui->comboBox_left->addItem("Select");
    ui->comboBox_right->addItem("Select");

    for (int i = 1; i <= totalPins; ++i) {
        ui->comboBox_left->addItem(QString::number(i));
        ui->comboBox_right->addItem(QString::number(i));
    }

    ui->comboBox_left->update();
    ui->comboBox_right->update();

}

void MainWindow::on_pushButton_update_clicked()
{
    fillCombos();
}
