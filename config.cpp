#include "config.h"
#include "ui_config.h"

config::config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::config)
{
    ui->setupUi(this);

    setWindowTitle("Config");

    connect(ui->spinBox_conCircles,SIGNAL(valueChanged(int)),this,SLOT(updateListItems(int)));

    updateListItems(ui->spinBox_conCircles->value());

}

config::~config()
{
    delete ui;
}

void config::updateListItems(int count)
{
    int currentItemCount = ui->listWidget->count();

            // Add items if the new count is greater than the current count
            if (count > currentItemCount) {
                for (int i = currentItemCount; i < count; ++i) {
                    QListWidgetItem *item = new QListWidgetItem(tr("Item %1").arg(i + 1), ui->listWidget);
                    item->setFlags(item->flags() | Qt::ItemIsEditable);  // Make items editable

                    QListWidgetItem *item2 = new QListWidgetItem(tr("Item %1").arg(i + 1), ui->listWidget_offset);
                    item2->setFlags(item->flags() | Qt::ItemIsEditable);  // Make items editable
                }
            }
            // Remove items if the new count is less than the current count
            else if (count < currentItemCount) {
                for (int i = currentItemCount - 1; i >= count; --i) {
                    delete ui->listWidget->takeItem(i);  // Remove item from the list
                    delete ui->listWidget_offset->takeItem(i);  // Remove item from the list

                }
            }
}

void config::on_pushButton_genPins_clicked()
{
    QStringList errorConditionList;
    pinArray.clear();
    floatArray.clear();
    angleOfRotation = 0;
    totalPins = 0;


    int totalSum = 0;
    totalPins = ui->spinBox_totalPins->value();
    angleOfRotation = ui->doubleSpinBox_angleOfRot->value();



    // Loop through all items in the QListWidget
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);  // Get each item
        QListWidgetItem *item2 = ui->listWidget_offset->item(i); // Get each item in offset List Widget
        bool ok;
        bool ok2;
        int value = item->text().toInt(&ok);  // Convert the item text to an integer
        float value2 = item2->text().toFloat(&ok2);  // Convert the item text to an float

        if (ok) {  // Check if conversion to int was successful
            errorConditionList.append("1");
            totalSum += value;
        } else {
            errorConditionList.append("0");
            QMessageBox::warning(this,"Error","Invalid integer in item "+item->text());
        }

        if (ok2) {  // Check if conversion to float was successful
            // Validate that value2 is between 0.1 and 1
            if (value2 < 0.1 || value2 > 1) {
                errorConditionList.append("0");
                QMessageBox::warning(this, "Error", "Value must be between 0.1 and 0.9 in item " + item->text());
            } else {
                errorConditionList.append("1");
                floatArray.append(value2);
            }
        }else {
            errorConditionList.append("0");
            QMessageBox::warning(this,"Error","Invalid float in item "+item->text());
        }
    }

    qDebug() << "Total Sum:" << totalSum;  // Display the total sum for debugging

    if(totalPins == totalSum)
    {
        for (int i = 0; i < ui->listWidget->count(); ++i) {
            QListWidgetItem *item = ui->listWidget->item(i);  // Get each item
            bool ok;
            int value = item->text().toInt(&ok);  // Convert the item text to an integer
            if (ok) {  // Check if conversion to int was successful
                errorConditionList.append("1");
                pinArray.append(value);
            } else {
                errorConditionList.append("0");
                QMessageBox::warning(this,"Error","Invalid integer in item "+item->text());
            }            
        }
        qDebug()<<pinArray<<" from config";
        qDebug()<<floatArray<<" from config";
        qDebug()<<angleOfRotation<<" from config";
        qDebug()<<totalPins<<" from config";

    }
    else
    {
        errorConditionList.append("0");
        QMessageBox::warning(this,"Error","Total No of Pins and Sum Of Concentric Pins Must Be Equal");
    }

    qDebug()<<errorConditionList;
    // Check if errorConditionList does NOT contain '0' and every element is '1'
    if (!errorConditionList.contains("0") && errorConditionList.count("1") == errorConditionList.size())
    {
        QMessageBox::information(this, "Success", "Pins Generated Successfully\n"
                                                  "Please Touch MainWindow to see changes");
    }


}

