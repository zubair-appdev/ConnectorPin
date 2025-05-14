#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <defines.h>

namespace Ui {
class config;
}

class config : public QDialog
{
    Q_OBJECT

public:
    explicit config(QWidget *parent = nullptr);
    ~config();

private:
    Ui::config *ui;

private slots:
    void updateListItems(int);
    void on_pushButton_genPins_clicked();


};

#endif // CONFIG_H
