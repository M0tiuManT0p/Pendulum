#include "lib.h"

//https://www.myphysicslab.com/pendulum/double-pendulum-en.html


double Radians(double Angle){
    return Angle * PI / 180;
}

double Square(double number){
    return number * number;
}

Points Cords(StartingData Data, State State, Point stable){
    Points points;

    points.p1.x = stable.x + Data.Length1 * sin(State.Angle1);
    points.p1.y = stable.y + Data.Length1 * cos(State.Angle1);

    points.p2.x = points.p1.x + Data.Length2 * sin(State.Angle2);
    points.p2.y = points.p1.y + Data.Length2 * cos(State.Angle2);

    return points;
}
Acceleration AccelerationFunction(StartingData Data, State State){
    Acceleration Acc;

    double m1 = Data.Mass1;
    double m2 = Data.Mass2;

    double l1 = Data.Length1;
    double l2 = Data.Length2;

    double g = Data.g;

    double a1 = State.Angle1;
    double a2 = State.Angle2;

    double v1 = State.Velocity1;
    double v2 = State.Velocity2;

    double num1 = -g * (2 * m1 + m2) * sin(a1) 
                  - m2 * g * sin(a1 - 2 * a2) 
                  - 2 * sin(a1 - a2) * m2 * (Square(v2) * l2 + Square(v1) * l1 * cos(a1 - a2));

    double denum1 = l1 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));

    Acc.Acceleration1 = num1 / denum1;

    double num2 = 2 * sin(a1 - a2) * (Square(v1) * l1 * (m1 + m2) 
              + g * (m1 + m2) * cos(a1) 
              + Square(v2) * l2 * m2 * cos(a1 - a2));

    double denum2 = l2 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));

    Acc.Acceleration2 = num2 / denum2;

    return Acc;
}

State UpdateState(StartingData Data, State state, double Time){
    State current = state;

    Acceleration Acc1 = AccelerationFunction(Data, current);

    double k1_v1 = Acc1.Acceleration1;
    double k1_v2 = Acc1.Acceleration2;
    
    double k1_a1 = current.Velocity1;
    double k1_a2 = current.Velocity2;

    State s1;
    s1.Velocity1 = current.Velocity1 + k1_v1 * (Time / 2.0);
    s1.Velocity2 = current.Velocity2 + k1_v2 * (Time / 2.0);

    s1.Angle1 = current.Angle1 + k1_a1 * (Time / 2.0);
    s1.Angle2 = current.Angle2 + k1_a2 * (Time / 2.0);

    Acceleration Acc2 = AccelerationFunction(Data, s1);

    double k2_v1 = Acc2.Acceleration1;
    double k2_v2 = Acc2.Acceleration2;
    
    double k2_a1 = s1.Velocity1;
    double k2_a2 = s1.Velocity2;

    State s2;
    s2.Velocity1 = current.Velocity1 + k2_v1 * (Time / 2.0);
    s2.Velocity2 = current.Velocity2 + k2_v2 * (Time / 2.0);

    s2.Angle1 = current.Angle1 + k2_a1 * (Time / 2.0);
    s2.Angle2 = current.Angle2 + k2_a2 * (Time / 2.0);

    Acceleration Acc3 = AccelerationFunction(Data, s2);

    double k3_v1 = Acc3.Acceleration1;
    double k3_v2 = Acc3.Acceleration2;
    
    double k3_a1 = s2.Velocity1;
    double k3_a2 = s2.Velocity2;

    State s3;
    s3.Velocity1 = current.Velocity1 + k3_v1 * Time;
    s3.Velocity2 = current.Velocity2 + k3_v2 * Time;

    s3.Angle1 = current.Angle1 + k3_a1 * Time;
    s3.Angle2 = current.Angle2 + k3_a2 * Time;

    Acceleration Acc4 = AccelerationFunction(Data, s3);

    double k4_v1 = Acc4.Acceleration1;
    double k4_v2 = Acc4.Acceleration2;
    
    double k4_a1 = s3.Velocity1;
    double k4_a2 = s3.Velocity2;

    current.Velocity1 = current.Velocity1 + (Time / 6.0) * (k1_v1 + 2.0*k2_v1 + 2.0*k3_v1 + k4_v1);
    current.Velocity2 = current.Velocity2 + (Time / 6.0) * (k1_v2 + 2.0*k2_v2 + 2.0*k3_v2 + k4_v2);

    current.Angle1 = current.Angle1 + (Time / 6.0) * (k1_a1 + 2.0*k2_a1 + 2.0*k3_a1 + k4_a1);
    current.Angle2 = current.Angle2 + (Time / 6.0) * (k1_a2 + 2.0*k2_a2 + 2.0*k3_a2 + k4_a2);

    return current;
}