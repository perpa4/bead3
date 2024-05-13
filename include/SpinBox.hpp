#ifndef SPINBOX_HPP
#define SPINBOX_HPP

#include "graphics.hpp"
#include "Widget.hpp"

#include "vector"
#include "string"

using namespace std;
using namespace genv;

class SpinBox : public Widget {
protected:
    int minValue;
    int maxValue;
    int value; //Intervallum és jelenlegi érték
    int spinBoxWidth, spinBoxHeight ,titleBarThickness; //Spinbox tulajdonságai
    int buttonWidth, buttonX, buttonY; //Gomb tulajdonságai

    bool isPressedAdd, isPressedSubtract; //Megnyomva van-e
    int deltaX, deltaY; // Mozgatáshoz delta értékek
    bool isDragging; // Mozgatás állapota

public:

    //Konstruktor
    SpinBox(int x, int y, int w, int h, string windowTitle, int minValue, int maxValue);

    //Rajzoló
    virtual void Draw();

    int setValue(int newValue);

    //Event Handler
    virtual void EventHandler(int mouseX, int mouseY, event ev);

    virtual string GetValue();
};

#endif // SPINBOX_HPP
