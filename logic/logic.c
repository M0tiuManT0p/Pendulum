#include "lib.h"

//https://www.myphysicslab.com/pendulum/double-pendulum-en.html

double Radians(double Angle) {
    return Angle * PI / 180;
}

double Degrees(double Angle) {
    return Angle * 180.0 / PI;
}

double Square(double number) {
    return number * number;
}

void Cords(Pendulum *p) {
    p->points.p1.x = p->stable.x + p->data.Length1 * sin(p->state.Angle1);
    p->points.p1.y = p->stable.y + p->data.Length1 * cos(p->state.Angle1);

    p->points.p2.x = p->points.p1.x + p->data.Length2 * sin(p->state.Angle2);
    p->points.p2.y = p->points.p1.y + p->data.Length2 * cos(p->state.Angle2);
}

void AccelerationFunction(Pendulum *p) {
    double m1 = p->data.Mass1;
    double m2 = p->data.Mass2;

    double l1 = p->data.Length1;
    double l2 = p->data.Length2;

    double g = p->data.g;

    double a1 = p->state.Angle1;
    double a2 = p->state.Angle2;

    double v1 = p->state.Velocity1;
    double v2 = p->state.Velocity2;

    double num1 = -g * (2 * m1 + m2) * sin(a1) 
                  - m2 * g * sin(a1 - 2 * a2) 
                  - 2 * sin(a1 - a2) * m2 * (Square(v2) * l2 + Square(v1) * l1 * cos(a1 - a2));

    double denum1 = l1 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));

    double a1pure = num1 / denum1;
    p->acc.Acceleration1 = a1pure - (p->AirResistance * p->state.Velocity1 / p->data.Mass1);

    double num2 = 2 * sin(a1 - a2) * (Square(v1) * l1 * (m1 + m2) 
              + g * (m1 + m2) * cos(a1) 
              + Square(v2) * l2 * m2 * cos(a1 - a2));

    double denum2 = l2 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));

    double a2pure = num2 / denum2;
    p->acc.Acceleration2 = a2pure - (p->AirResistance * p->state.Velocity2 / p->data.Mass2);
}

double RungeKuttaSwitch(Pendulum p, int data) {
    switch (data) {
        case 1: return p.state.Angle1;
        case 2: return p.state.Angle2;
        case 3: return p.state.Velocity1;
        case 4: return p.state.Velocity2;
        default: return 0.0;
    }
}

double RungeKuttaDerivative(Pendulum p, int data) {
    switch (data) {
        case 1: return p.state.Velocity1;
        case 2: return p.state.Velocity2;
        case 3: return p.acc.Acceleration1;
        case 4: return p.acc.Acceleration2;
        default: return 0.0;
    }
}

void SetTempState(Pendulum *p, int data, double value) {
    switch (data) {
        case 1: p->state.Angle1 = value; break;
        case 2: p->state.Angle2 = value; break;
        case 3: p->state.Velocity1 = value; break;
        case 4: p->state.Velocity2 = value; break;
    }
}

double RungeKutta(Pendulum p, double Time, int data) {
    double current = RungeKuttaSwitch(p, data);

    AccelerationFunction(&p);
    double k1 = RungeKuttaDerivative(p, data);

    Pendulum p2 = p;
    SetTempState(&p2, data, current + k1 * (Time / 2.0));
    AccelerationFunction(&p2);
    double k2 = RungeKuttaDerivative(p2, data);

    Pendulum p3 = p;
    SetTempState(&p3, data, current + k2 * (Time / 2.0));
    AccelerationFunction(&p3);
    double k3 = RungeKuttaDerivative(p3, data);

    Pendulum p4 = p;
    SetTempState(&p4, data, current + k3 * Time);
    AccelerationFunction(&p4);
    double k4 = RungeKuttaDerivative(p4, data);

    return current + (Time / 6.0) * (k1 + 2.0*k2 + 2.0*k3 + k4);
}

double AngleWrap(double angle) {
    while (angle > PI) angle -= 2.0 * PI;
    while (angle < -PI) angle += 2.0 * PI;
    return angle;
}

void UpdateState(Pendulum *p, double Time, bool showAftermark) {
    for (int i = 0; i < p->speed; i++) {
        p->state.Angle1 = AngleWrap(RungeKutta(*p, Time, 1));
        p->state.Angle2 = AngleWrap(RungeKutta(*p, Time, 2));

        p->state.Velocity1 = RungeKutta(*p, Time, 3);
        p->state.Velocity2 = RungeKutta(*p, Time, 4);
    }

    Cords(p);

    if (showAftermark == true) {
        p->history[p->count].x = p->points.p2.x - p->stable.x;
        p->history[p->count].y = p->points.p2.y - p->stable.y;
        p->count++;
        p->count = p->count %maxHistory;
    }
}