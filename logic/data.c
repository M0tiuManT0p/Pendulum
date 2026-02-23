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

    pendulum1.color = BLUE;

    pendulum1.speed = 100;

    for (int i = 0; i < maxHistory; i++) {
        pendulum1.history[i].x = 0;
        pendulum1.history[i].y = 0;
    }

    pendulum1.count = 0;

    return pendulum1;
}

// Pendulum InitPendulum2(void){
//     Pendulum pendulum2;

//     pendulum2.data.Length1 = 150.00;
//     pendulum2.data.Length2 = 200.00;

//     pendulum2.data.Mass1 = 2.00;
//     pendulum2.data.Mass2 = 2.00;

//     pendulum2.data.g = 9.81;

//     pendulum2.state.Angle1 = Radians(45);
//     pendulum2.state.Angle2 = Radians(-45);

//     pendulum2.state.Velocity1 = 0.0;
//     pendulum2.state.Velocity2 = 0.0;

//     pendulum2.stable.x = (screenWidth / 3) * 2;
//     pendulum2.stable.y = screenHeight - (screenHeight / 3) * 2 ;

//     pendulum2.points = Cords(pendulum2.data, pendulum2.state, pendulum2.stable);

//     for (int i = 0; i < 255; i++) {
//         pendulum2.history[i] = pendulum2.points.p2; 
//     }

//     pendulum2.count = 0;

//     return pendulum2;
// }

// Pendulum InitPretzel(void){
//     Pendulum pretzel;

//     pretzel.data.Length1 = 120.00;
//     pretzel.data.Length2 = 120.00;

//     pretzel.data.Mass1 = 2.00;
//     pretzel.data.Mass2 = 2.00;

//     pretzel.data.g = 9.81;

//     pretzel.state.Angle1 = 2.49;
//     pretzel.state.Angle2 = 0.25;

//     pretzel.state.Velocity1 = 0.0;
//     pretzel.state.Velocity2 = 0.0;

//     pretzel.stable.x = screenWidth / 2;
//     pretzel.stable.y = screenHeight - (screenHeight / 3) * 2 ;

//     pretzel.points = Cords(pretzel.data, pretzel.state, pretzel.stable);

//     for (int i = 0; i < 1000; i++) {
//         pretzel.history[i] = pretzel.points.p2; 
//     }

//     pretzel.count = 0;

//     return pretzel;
// }

