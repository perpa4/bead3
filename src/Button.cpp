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
Button::Button(int x, int y, int w, int h, int textSize, string value) : Widget(x, y, w, h), textSize(textSize), value(value), isPressed(false) {}

//Rajzoló
void Button::Draw() {
    gout << font("LiberationSans-Regular.ttf",textSize);
    //Gomb
    if (isPressed) gout << move_to(x, y) << color(21, 44, 55) << box(w, h);
    else gout <<  move_to(x, y) << color(31, 54, 65) << box(w, h);


    //Érték
    gout << move_to(x + w/2 - gout.twidth(value)/2, y + h/2 - gout.cascent()/1.5) << color(230,239,246) << text(value);
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
        }
    }
    if (ev.button == -btn_left) {
        isPressed = false;
    }
}

string Button::GetValue() {
    return value;
};
