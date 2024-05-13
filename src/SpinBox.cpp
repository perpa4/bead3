#include "SpinBox.hpp"
#include "graphics.hpp"
#include "iostream"

#include "vector"
#include "string"

using namespace std;
using namespace genv;

const int XX = 800;
const int YY = 800;

//Konstruktor
SpinBox::SpinBox(int x, int y, int w, int h, string windowTitle, int minValue, int maxValue) : Widget(x, y, w, h, windowTitle), minValue(minValue), maxValue(maxValue), value(minValue), spinBoxWidth(200), spinBoxHeight(50), titleBarThickness(30), buttonWidth(30),
buttonX(x + (w / 2) + (spinBoxWidth / 2) - buttonWidth), buttonY(buttonY = y + (h / 2) - (spinBoxHeight / 2) + 2), isPressedAdd(false), isPressedSubtract(false), isDragging(false) {}

//Rajzoló
void SpinBox::Draw() {
    gout << font("LiberationSans-Regular.ttf",15);

    //ToolBar
    gout << move_to(x, y - titleBarThickness) << color(255, 255, 255) << box(w, titleBarThickness);
    //Szöveg
    gout << move_to(x + 10, y - 25) << color(0, 0, 0) << text(windowTitle);

    //Ablak
    gout << move_to(x, y) << color(240,240,240) << box(w,h);

    //Spinbox
    gout << move_to(x + (w / 2) - (spinBoxWidth / 2), y + (h / 2) - (spinBoxHeight / 2)) << color(160, 160, 160) << box(spinBoxWidth, spinBoxHeight)
         << move_to(x + (w / 2) + 2 - (spinBoxWidth / 2), y + (h / 2) + 2 - (spinBoxHeight / 2)) << color(255, 255, 255) << box(spinBoxWidth, spinBoxHeight);

    //Érték
    gout << move_to(x + (w / 2) - (spinBoxWidth / 2) + 10, y + (h / 2) - (spinBoxHeight/2) + (gout.cascent()/2)) << color(0,0,0) << font("LiberationSans-Regular.ttf",30) << text(to_string(value));

    //Gombok
    //Hozzáadó
    gout << move_to(buttonX, buttonY) << color(105, 105, 105) << box(buttonWidth, (spinBoxHeight / 2) - 1)
         << move_to(buttonX, buttonY) << color(255, 255, 255) << box(buttonWidth - 2, (spinBoxHeight / 2) - 3);

    if (isPressedAdd) gout <<  move_to(buttonX + 2, buttonY + 2) << color(200, 200, 200) << box(buttonWidth - 4, (spinBoxHeight / 2) - 5);
    else gout <<  move_to(buttonX + 2, buttonY + 2) << color(240, 240, 240) << box(buttonWidth - 4, (spinBoxHeight / 2) - 5);

    //Szöveg
    gout << move_to(x + (w / 2) + (spinBoxWidth / 2) - buttonWidth, y + (h / 2) - (spinBoxHeight / 4) - (gout.cascent() / 2) - 5) << color(0, 0, 0) << text("▲");

    //Kivonó
    gout << move_to(buttonX, buttonY + spinBoxHeight/2) << color(105, 105, 105) << box(buttonWidth, (spinBoxHeight / 2) - 1)
         << move_to(buttonX, buttonY + spinBoxHeight/2) << color(255, 255, 255) << box(buttonWidth - 2, (spinBoxHeight / 2) - 3);
    if (isPressedSubtract) gout << move_to(buttonX + 2, buttonY + 2  + spinBoxHeight/2) << color(200, 200, 200) << box(buttonWidth - 4, (spinBoxHeight / 2) - 5);
    else gout << move_to(buttonX + 2, buttonY + 2  + spinBoxHeight/2) << color(240, 240, 240) << box(buttonWidth - 4, (spinBoxHeight / 2) - 5);

    //Szöveg
    gout << move_to(x + (w / 2) + (spinBoxWidth / 2) - buttonWidth, y + (h / 2) + (spinBoxHeight / 4) - (gout.cascent() / 2) - 5) << color(0, 0, 0) << text("▼");
}

int SpinBox::setValue(int newValue) {
    value = newValue;
}

//Event Handler
void SpinBox::EventHandler(int mouseX, int mouseY, event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left) {
        if (mouseX > x &&
            mouseX < x + w &&
            mouseY > (y - titleBarThickness) &&
            mouseY < y)
        {
            cout << "Dragging" << endl;;
            isDragging = true;
            deltaX = mouseX - x;
            deltaY = mouseY - y;
        }
    }

    //Hozzáadás gombbal
    // Egyesével
    if (ev.keycode == key_up && value + 1 <= maxValue) setValue(value + 1);
    if (ev.keycode == key_down && value - 1 >= minValue) setValue(value - 1);
    // Tízesével
    if (ev.keycode == key_pgup && value + 10 <= maxValue) setValue(value + 10);
    if (ev.keycode == key_pgdn && value - 10 >= minValue) setValue(value - 10);

    if (isDragging) {
        int newX = ev.pos_x - deltaX;
        int newY = ev.pos_y - deltaY;

        //Legjobb dolog amit felfedeztem
        newX = max(0, min(newX, XX - w));
        newY = max(30, min(newY, YY - h));

        x = newX;
        y = newY;

        buttonX = x + (w / 2) + (spinBoxWidth / 2) - buttonWidth;
        buttonY = y + (h / 2) - (spinBoxHeight / 2) + 2;
    }

    if (ev.button == -btn_left) isDragging = false;

    //Hozzáadó
    if (ev.button == btn_left) {
        if (mouseX > buttonX &&
            mouseX < buttonX + buttonWidth &&
            mouseY > buttonY &&
            mouseY < buttonY + (spinBoxHeight / 2))
        {
            isPressedAdd = true;
            cout << "Touch" << endl;;
            if (value+1 <= maxValue) setValue(value+1);
        }
        if (mouseX > buttonX &&
            mouseX < buttonX + buttonWidth &&
            mouseY > buttonY + (spinBoxHeight / 2) &&
            mouseY < buttonY + spinBoxHeight)
        {
            isPressedSubtract = true;
            cout << "Touch" << endl;;
            if (value-1 >= minValue) setValue(value-1);
        }
    }
    if (ev.button == -btn_left) {
        isPressedAdd = false;
        isPressedSubtract = false;
    }
}

string SpinBox::GetValue() {
    return to_string(value);
};
