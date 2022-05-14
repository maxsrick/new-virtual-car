#include "track.h"
#include "car.h"
#include "physics.h"
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include <QFile>
#include <QDebug>

using namespace std;

track::track()
{
    m_c_static_friction = 0.7; //change to typical value for asphalt
    m_c_dynamic_friction = 0.6; //change to typical value for asphalt
    m_fluid_density = 1.292; //typical value for air at room pressure and standard atm press.
    m_total_length = 0.0;

    //reading in coordinates, qt style
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
        temp.push_back(v1.toDouble());
        temp.push_back(v2.toDouble());
        temp.push_back(v3.toDouble());
        m_coordinates.push_back(temp);
    }

    for (unsigned long i=0; i < m_coordinates.size()-1; i++) //calculating total length
    {
        double d = distance_between_coordinates(&m_coordinates[i], &m_coordinates[i+1]);
        m_total_length += d;
    }
}

  //accessor methods
double track::get_c_static_friction() {return m_c_static_friction;}
double track::get_c_dynamic_friction() {return m_c_dynamic_friction;}
double track::get_fluid_density() {return m_fluid_density;}
double track::get_total_length() {return m_total_length;}

  //mutator methods - note: adjust angles and density for gravity, etc.

void track::set_c_static_friction(double csf) {m_c_static_friction = csf;}
void track::set_c_dynamic_friction(double cdf) {m_c_dynamic_friction = cdf;}
void track::set_fluid_density(double fd) {m_fluid_density = fd;}

double track::time_to_run(car* Car)
{
    double time = 0.0;
    for (unsigned long i=0; i < m_coordinates.size()-1; i++) //calculating total length
    {
        double s = distance_between_coordinates(&m_coordinates[i], &m_coordinates[i+1]);
        double incline_angle = angle_between_coordinates(&m_coordinates[i], &m_coordinates[i+1]);
        Car->set_orientation(incline_angle);
        double u = Car->get_velocity();
        double old_nf = Car->get_net_force_x();
        Car->set_engine_force(-1.0*old_nf); //set engine force to stay at 15mph??
        double net_force_x = Car->get_net_force_x();
        double a = net_force_x / Car->get_mass();
        double v = v_uas(u, a, s);
        double t = t_usa(u, s, a);
        Car->travel(s);
        Car->set_velocity(v);
        Car->climb(s*sin(incline_angle));
        Car->set_engine_force(0);
        //qDebug() << t;
        time += t;
    }
    return time;
}

double track::time_one_segment(car *Car, vector<double>* c1, vector<double>* c2)
{
    double s = distance_between_coordinates(c1, c2);
    double incline_angle = angle_between_coordinates(c1, c2);
    Car->set_orientation(incline_angle);
    double u = Car->get_velocity();
    double old_nf = Car->get_net_force_x();
    Car->set_engine_force(-1.0*old_nf); //set engine force to stay at 15mph??
    double net_force_x = Car->get_net_force_x();
    double a = net_force_x / Car->get_mass();
    double v = v_uas(u, a, s);
    double t = t_usa(u, s, a);
    Car->travel(s);
    Car->set_velocity(v);
    Car->climb(s*sin(incline_angle));
    Car->set_engine_force(0);
    return t;
}

double track::distance_between_coordinates(vector<double>* c1, vector<double>* c2)
{
    double x1 = (*c1)[0];
    double y1 = (*c1)[1];
    double z1 = (*c1)[2];

    double x2 = (*c2)[0];
    double y2 = (*c2)[1];
    double z2 = (*c2)[2];

    double dist = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y2) + (z2-z1)*(z2-z1));
    return dist;
}

double track::angle_between_coordinates(vector<double>* c1, vector<double>* c2)
{
    double delta_z = (*c1)[2] - (*c2)[2];
    double dist = distance_between_coordinates(c1, c2);
    double angle = (-1.0)*asin(delta_z/dist); //retaining sign conventions
    return angle;
}
