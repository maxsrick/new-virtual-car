#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "runner.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    units = true;
    //this->setStyleSheet("background-color: darkBlue;");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "yay";
}


void MainWindow::on_pushButton_2_clicked()
{
    runner r(ui->doubleSpinBox->value(), ui->doubleSpinBox_3->value(), ui->doubleSpinBox_2->value(), units);
    r.setModal(true);
    r.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    if (ui->pushButton_3->text() == "Imperial")
    {
        ui->pushButton_3->setText("Metric");
        ui->doubleSpinBox->setValue(ui->doubleSpinBox->value() / 2.20462262);
        ui->doubleSpinBox_2->setValue(ui->doubleSpinBox_2->value() / 2.237);
        ui->label->setText("Weight (kg)");
        ui->label_2->setText("Speed (m/s)");
        units = false;
    }
    else //(ui->pushButton_3->text() == "Metric")
    {
        ui->pushButton_3->setText("Imperial");
        ui->doubleSpinBox->setValue(ui->doubleSpinBox->value() * 2.20462262);
        ui->doubleSpinBox_2->setValue(ui->doubleSpinBox_2->value() * 2.237);
        ui->label->setText("Weight (lb)");
        ui->label_2->setText("Wpeed (mph)");
        units = true;
    }
}
