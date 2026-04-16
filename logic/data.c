#include "lib.h"

Pendulum InitPendulum1(void){
    Pendulum pendulum1;

    pendulum1.data.Length1 = 100.00;
    pendulum1.data.Length2 = 150.00;

    pendulum1.data.Mass1 = 30.00;
    pendulum1.data.Mass2 = 30.00;

    pendulum1.data.g = 100;

    pendulum1.state.Angle1 = Radians(35);
    pendulum1.state.Angle2 = Radians(-35);

    pendulum1.state.Velocity1 = 0.0;
    pendulum1.state.Velocity2 = 0.0;

    pendulum1.stable.x = 0; 
    pendulum1.stable.y = 0;

    pendulum1.AirResistance = 0;

    pendulum1.color = DARKGRAY;

    pendulum1.speed = 100;

    for (int i = 0; i < maxHistory; i++) {
        pendulum1.history[i].x = 0;
        pendulum1.history[i].y = 0;
    }

    pendulum1.count = 0;

    return pendulum1;
}

void ResetPendulum(Pendulum *p) {
    p->state.Angle1 = Radians(35);
    p->state.Angle2 = Radians(-35);
    
    p->state.Velocity1 = 0.0;
    p->state.Velocity2 = 0.0;
    
    for (int i = 0; i < maxHistory; i++) {
        p->history[i].x = 0;
        p->history[i].y = 0;
    }
    p->count = 0;
    
    Cords(p);
}

void ApplyPreset(Pendulum *p, int preset) {
    if (preset == 1) { // Pretzel
        p->data.Length1 = 120.0; p->data.Length2 = 120.0;
        p->data.Mass1 = 2.0; p->data.Mass2 = 2.0;
        p->data.g = 9.81;
        p->state.Angle1 = 2.49; p->state.Angle2 = 0.25;
    } else if (preset == 2) { // Small Angle
        p->data.Length1 = 100.0; p->data.Length2 = 100.0;
        p->data.Mass1 = 10.0; p->data.Mass2 = 10.0;
        p->data.g = 9.81;
        p->state.Angle1 = Radians(5); p->state.Angle2 = 0.0;
    } else if (preset == 3) { // In-Phase
        p->data.Length1 = 100.0; p->data.Length2 = 100.0;
        p->data.Mass1 = 10.0; p->data.Mass2 = 10.0;
        p->data.g = 9.81;
        p->state.Angle1 = Radians(10); p->state.Angle2 = Radians(14.14);
    } else if (preset == 4) { // Anti-Phase
        p->data.Length1 = 100.0; p->data.Length2 = 100.0;
        p->data.Mass1 = 10.0; p->data.Mass2 = 10.0;
        p->data.g = 9.81;
        p->state.Angle1 = Radians(10); p->state.Angle2 = Radians(-14.14);
    }

    p->state.Velocity1 = 0.0;
    p->state.Velocity2 = 0.0;
    p->count = 0;

    for (int i = 0; i < maxHistory; i++) {
        p->history[i].x = 0;
        p->history[i].y = 0;
    }
    
    Cords(p);
}