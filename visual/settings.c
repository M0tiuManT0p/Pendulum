#include "lib.h"

Rectangle PointsToRect(Points p) {
    Rectangle rect;
    rect.x = p.p1.x;
    rect.y = p.p1.y;
    rect.width = p.p2.x - p.p1.x;
    rect.height = p.p2.y - p.p1.y;
    
    return rect;
}

bool DrawSettingsButton(void){

    GuiSetIconScale(2); 

    Points p;

    p.p1.x = SCREEN_WIDTH - 48;
    p.p1.y = 24;

    p.p2.x = SCREEN_WIDTH - 24;
    p.p2.y = 48;

    bool pressed = GuiLabelButton((PointsToRect(p)), "#142#");
    GuiSetIconScale(1);
    return pressed;
}

bool SettingsWindow(void){

    Points p;

    p.p1.x = SCREEN_WIDTH - (SCREEN_WIDTH / 3);
    p.p1.y = 0;

    p.p2.x = SCREEN_WIDTH;
    p.p2.y = SCREEN_HEIGHT;

    bool pressed = GuiWindowBox((PointsToRect(p)), "#198# SETTINGS");
    return pressed;
}