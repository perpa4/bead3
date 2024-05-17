#include "Button.hpp"
#include "graphics.hpp"
#include "iostream"

#include "vector"
#include "string"

using namespace std;
using namespace genv;

const int XX = 800;
const int YY = 800;

//Konstruktor
Button::Button(int x, int y, int w, int h, string windowTitle, int textSize, string value) : Widget(x, y, w, h, windowTitle), textSize(textSize), value(value), isPressed(false) {}

//Rajzoló
void Button::Draw() {
    gout << font("LiberationSans-Regular.ttf",textSize);
    //Gomb
    gout << move_to(x, y) << color(105, 105, 105) << box(w, h)
         << move_to(x, y) << color(255, 255, 255) << box(w - 2, h - 3);
    if (isPressed) gout <<  move_to(x + 2, y + 2) << color(200, 200, 200) << box(w - 4, h - 5);
    else gout <<  move_to(x + 2, y + 2) << color(240, 240, 240) << box(w - 4, h - 5);


    //Érték
    gout << move_to(x + w/2 - gout.twidth("Click!")/2, y + h/2 - gout.cascent()/1.5) << color(0,0,0) << text(value);
}

//Event Handler
void Button::EventHandler(int mouseX, int mouseY, event ev) {
    //Hozzáadó
    if (ev.button == btn_left) {
        if (mouseX > x &&
            mouseX < x + w &&
            mouseY > y &&
            mouseY < y + h)
        {
            isPressed = true;
            cout << "Touch" << endl;;
            value = "str";
        }
    }
    if (ev.button == -btn_left) {
        isPressed = false;
    }
}

string Button::GetValue() {
    return value;
};
