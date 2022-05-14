#ifndef RUNNER_H
#define RUNNER_H

#include <QDialog>
#include "track.h"
#include "car.h"
#include "qcustomplot.h"

namespace Ui {
class runner;
}

class runner : public QDialog
{
    Q_OBJECT

public:
    explicit runner(double mass, int laps, double speed, bool units, QWidget *parent = nullptr);
    ~runner();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::runner *ui;
    QVector<double> x;
    QVector<double> y;
    QVector<double> z;
    QVector<double> x2;
    QVector<double> y2;
    double time;
    double distance;
    double avg_v;
    int i;
    QElapsedTimer timer;
    QString tStr;
    QString msStr;
    QString dStr;
    double m_speed;
    double m_mass;
    double m_laps;
    bool m_units;
};

#endif // RUNNER_H
