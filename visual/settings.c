#include "lib.h"

Rectangle PointsToRect(Points p) {
    Rectangle rect;
    rect.x = p.p1.x;
    rect.y = p.p1.y;
    rect.width = p.p2.x - p.p1.x;
    rect.height = p.p2.y - p.p1.y;
    
    return rect;
}

bool DrawSettingsButton(void) {
    int sw = GetScreenWidth();

    float btnSize = 40.0f;
    float margin = 20.0f;

    int iconScale = (sw > 1200) ? 2 : 1; 
    GuiSetIconScale(iconScale);

    Rectangle btnRect = { 
        (float)sw - btnSize - margin,
        margin,
        btnSize,
        btnSize
    };

    bool pressed = GuiLabelButton(btnRect, GuiIconText(142, ""));

    GuiSetIconScale(1);
    
    return pressed;
}
bool SettingsWindow(Pendulum *pendulum) {
    Points p;
    p.p1.x = GetScreenWidth() - (GetScreenWidth() / 3);
    p.p1.y = 0;
    p.p2.x = GetScreenWidth();
    p.p2.y = GetScreenHeight();

    Rectangle windowRect = PointsToRect(p);
    GuiSetStyle(DEFAULT, BACKGROUND_COLOR, ColorToInt(GetColor(0x1c1c1ccc)));
    bool pressed = GuiWindowBox(windowRect, "#198# SETTINGS");

    float startX = windowRect.x + 20;
    float startY = 80;
    static bool editL1 = false;
    static bool editL2 = false;

    LengthSettings(pendulum, startX, startY, &editL1, true);
    LengthSettings(pendulum, startX, startY + 60, &editL2, false);

    return pressed;
}

void LengthSettings(Pendulum *pendulum, float startX, float startY, bool *editMode, bool isFirst) {
    double *targetLen = isFirst ? &pendulum->data.Length1 : &pendulum->data.Length2;
    const char *label = isFirst ? "Length 1" : "Length 2";

    GuiLabel((Rectangle){ startX, startY, 100, 20 }, label);

    float fLen = (float)(*targetLen);
    int iLen = (int)(*targetLen);

    GuiSlider((Rectangle){ startX + 80, startY, 120, 20 }, "10", "300", &fLen, 10, 300);
    if (GuiValueBox((Rectangle){ startX + 230, startY, 60, 20 }, NULL, &iLen, 10, 300, *editMode)) {
        *editMode = !(*editMode);
    }

    if ((int)fLen != (int)(*targetLen) || iLen != (int)(*targetLen)) {
        *targetLen = (fLen != (float)(*targetLen)) ? (double)fLen : (double)iLen;

        pendulum->points = Cords(pendulum->data, pendulum->state, pendulum->stable);

        for (int i = 0; i < maxHistory; i++) {
            pendulum->history[i].x = pendulum->points.p2.x - pendulum->stable.x;
            pendulum->history[i].y = pendulum->points.p2.y - pendulum->stable.y;
        }
    }
}