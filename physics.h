//
//  physics.h
//  virtualCar
//
//  Created by Anay Mehta on 29/08/2020.
//  Copyright © 2020 Anay. All rights reserved.
//

//add error message for division by 0

#ifndef physics_h
#define physics_h

#include <math.h>
#include <iostream>
using namespace std;

// MARK: v^2 = u^2 + 2as

// v = sqrt(u^2 + 2as)
double v_uas(double u, double a, double s) {
    return sqrt(u*u + 2*a*s);
}

// u = sqrt(v^2 - 2as)
double u_vas(double v, double a, double s) {
    return sqrt(v*v - 2*a*s);
}

// (v^2 - u^2)/2s
double a_vus(double v, double u, double s) {
    if (s==0)
    {
        cout << "Divide by zero with physics.h equation a_vus" << endl;
        exit(0);
    }
    return ((v*v - u*u)/(2*s));
}

// (v^2 - u^2)/2a
double s_vua(double v, double u, double a) {
    if (a==0)
    {
        cout << "Divide by zero with physics.h equation s_vua" << endl;
        exit(0);
    }
    return ((v*v - u*u)/(2*a));
}



// MARK: v = u + at

// v = u + at
double v_uat(double u, double a, double t) {
    return (u + a*t);
}

// u = v - at
double u_vat(double v, double a, double t) {
    return (v - a*t);
}

// a = (v - u)/t
double a_vut(double v, double u, double t) {
    if (t==0)
    {
        cout << "Divide by zero with physics.h equation a_vut" << endl;
        exit(0);
    }
    return ((v - u)/t);
}

// t = (v - u)/a
double t_vua(double v, double u, double a) {
    if (a==0)
    {
        cout << "Divide by zero with physics.h equation t_vua" << endl;
        exit(0);
    }
    return ((v - u)/a);
}



// MARK: s = ut + (at^2)/2

// s = ut + (at^2)/2
double s_uat(double u, double a, double t) {
    return (u*t + 0.5*a*t*t);
}

// u = s/t - at/2
double u_sat(double s, double a, double t) {
    return (s/t - (a*t)/2);
}

// a = 2s/(t^2) - 2u/t
double a_ust(double u, double s, double t) {
    if (t==0)
    {
        cout << "Divide by zero with physics.h equation a_ust" << endl;
        exit(0);
    }
    return ((2*s)/(t*t) - (2*u)/t);
}

// t = (-u ± sqrt(u^2 + 2as))/a
double t_usa(double u, double s, double a) {
    if (a==0)
    {
        double t = s/u;
        if (t >= 0)
            return t;
        else
            return -t;
    }
    double t = (-u + sqrt(u*u + 2*a*s))/a;
    // We are only concerned with the positive value of time
    if (t >= 0)
        return t;
    else
        return -t;
}

#endif /* physics_h */
