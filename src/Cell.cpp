#include "Cell.hpp"
#include "graphics.hpp"
#include "vector"
#include "iostream"
#include "math.h"

#include "vector"
#include "string"

using namespace std;
using namespace genv;

Cell::Cell(int x, int y, int w, int h) : Widget(x, y, w, h), state(0) {}

void Cell::Draw() {
    gout << move_to(x+w/14, y+w/14) << color(31, 54, 65) << box(w - w/7, h - w/7);

    //Érték
    if (state == 1) {
        //X
        int margin = w / 5;
        int thickness = w / 5;

        gout << color(157, 204, 210);

        for (int i = 0; i < thickness; ++i) {
            gout << move_to(x + i + margin, y + margin) << line_to(x + w - thickness - margin + i, y + h - margin);
            gout << move_to(x + i + margin, y + h - margin) << line_to(x + w - thickness - margin + i, y + margin);
        }

    } else if (state == 2) {
        //O
        int margin = w / 5;
        int radius = (w - 2 * margin) / 2;
        int centerX = x + w / 2;
        int centerY = y + h / 2;
        int thickness = w / 8;

        for (int i = 0; i < thickness; ++i) {
            for (double j = 0; j <= 360; j += 0.2) {
                double angle = j * M_PI / 180;
                int endX = centerX + (radius - i) * cos(angle);
                int endY = centerY + (radius - i) * sin(angle);
                gout << move_to(endX, endY) << color(255, 135, 85) << dot;
            }
        }
    }
}

int Cell::getState() {
    return state;
}

void Cell::setState(int newState) {
    state = newState;
}

bool Cell::isHover(int mouse_x, int mouse_y) {
    return mouse_x >= x && mouse_x <= x + w && mouse_y >= y && mouse_y <= y + h;
}
