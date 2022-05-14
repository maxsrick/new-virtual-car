#include "runner.h"
#include "ui_runner.h"
#include <vector>

runner::runner(double mass, int laps, double speed, bool units, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::runner)
{
    m_speed = speed;
    m_mass = mass;
    m_laps = laps;
    m_units = units;
    time = 0.0;
    distance = 0.0;
    avg_v = 0.0;
    i = 0;
    ui->setupUi(this);
    //reading in coordinates for display, only doing 2D
    QFile file("/Users/maxrick/Virtual-Car/sonoma.csv");
    if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << file.errorString();
            exit(1);
        }
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        vector<double> temp;
        QString v1 = line.split(',').first();
        QString v2 = line.split(',').at(1);
        QString v3 = line.split(',').at(2);
        x.push_back(v1.toDouble());
        y.push_back(v2.toDouble());
        z.push_back(v3.toDouble());
    }
    x2.push_back(0.0);
    y2.push_back(0.0);
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(-325, 240);
    ui->customPlot->yAxis->setRange(-270, 310);
    ui->customPlot->xAxis->setVisible(false);
    ui->customPlot->yAxis->setVisible(false);
    ui->customPlot->axisRect()->setAutoMargins(QCP::msNone);
    ui->customPlot->axisRect()->setMargins(QMargins(0,0,0,0));
    //change color
    //ui->customPlot->setBackground(QColor(1,25,147));
    QPen pen1;
    pen1.setWidth(1);
    pen1.setColor(QColor(0,0,0));
    ui->customPlot->graph(0)->setPen(pen1);
    // make it a scatter graph
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    //add second graph to track progress
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setData(x2, y2);
    QPen pen2;
    pen2.setWidth(1);
    pen2.setColor(QColor(255,0,0));
    ui->customPlot->graph(1)->setPen(pen2);
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->customPlot->replot();

    /*track* t = new track;
    car* c = new car(t);
    c->set_mass(mass);
    double speed_choice = speed;
    speed_choice = speed_choice/2.237; //convert to m/s
    int lap_choice = laps;
    c->set_velocity(speed_choice);
    double time = 0.0;
    for(int i=0;i<lap_choice;i++)
        time += t->time_to_run(c);
    double l = 0.0;
    for(int j=0;j<lap_choice;j++)
        l += t->get_total_length();
    double ms = l/time;
    msStr = QString::number(ms, 'f', 2);
    msStr = msStr + " m/s";
    tStr = QString::number(time, 'f', 2);
    tStr = tStr + " s";
    dStr = QString::number(l, 'f', 2);
    dStr = dStr + " m";*/
}

runner::~runner()
{
    delete ui;
}

void runner::on_pushButton_clicked()
{
    track* t = new track;
    car* c = new car(t);
    c->set_mass(m_mass);
    double speed_choice = m_speed;
    speed_choice = speed_choice/2.237; //convert to m/s
    //int lap_choice = m_laps;
    c->set_velocity(speed_choice);
    vector<double>* c1 = new vector<double>;
    vector<double>* c2 = new vector<double>;
    if (i==0)
        timer.start();
    if (i==x.size())
        qDebug() << timer.elapsed();
    if (i==x.size()-1)
    {
        return;
    }
    else
    {
        x2.pop_back();
        y2.pop_back();
        x2.push_back(x[i]);
        y2.push_back(y[i]);
        c1->push_back(x[i]);
        c1->push_back(y[i]);
        c1->push_back(z[i]);
        c2->push_back(x[i+1]);
        c2->push_back(y[i+1]);
        c2->push_back(z[i+1]);
        time += t->time_one_segment(c, c1, c2);
        distance += t->distance_between_coordinates(c1, c2);
        avg_v = distance/time;
        //qDebug() << t->time_one_segment(c, c1, c2);
        tStr = QString::number(time, 'f', 2);
        tStr = tStr + " s";
        msStr = QString::number(avg_v, 'f', 2);
        msStr = msStr + " m/s";
        dStr = QString::number(distance, 'f', 2);
        dStr = dStr + " m";
        ui->label_6->setText(dStr);//display info
        ui->label_4->setText(msStr);
        ui->label_2->setText(tStr);
    }
    ui->customPlot->graph(1)->setData(x2, y2);
    ui->customPlot->replot();
    i++;
    //ui->label_6->setText("i");
    ui->pushButton->animateClick(t->time_one_segment(c, c1, c2)*1000);
    delete t;
    delete c;
    delete c1;
    delete c2;
}

void runner::on_pushButton_2_clicked()
{
    track* t = new track;
    car* c = new car(t);
    c->set_mass(m_mass);
    double speed_choice = m_speed;
    speed_choice = speed_choice/2.237; //convert to m/s
    int lap_choice = m_laps;
    c->set_velocity(speed_choice);
    double time = 0.0;
    for(int i=0;i<lap_choice;i++)
        time += t->time_to_run(c);
    double l = 0.0;
    for(int j=0;j<lap_choice;j++)
        l += t->get_total_length();
    double ms = l/time;
    msStr = QString::number(ms, 'f', 2);
    msStr = msStr + " m/s";
    tStr = QString::number(time, 'f', 2);
    tStr = tStr + " s";
    dStr = QString::number(l, 'f', 2);
    dStr = dStr + " m";
    ui->label_6->setText(dStr);//display info
    ui->label_4->setText(msStr);
    ui->label_2->setText(tStr);
    delete t;
    delete c;
}

void runner::on_pushButton_3_clicked()
{
    /*if (ui->pushButton_3->text() == "Imperial")
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
    }*/
}
