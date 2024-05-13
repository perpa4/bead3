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
    int value; //Intervallum �s jelenlegi �rt�k
    int spinBoxWidth, spinBoxHeight ,titleBarThickness; //Spinbox tulajdons�gai
    int buttonWidth, buttonX, buttonY; //Gomb tulajdons�gai

    bool isPressedAdd, isPressedSubtract; //Megnyomva van-e
    int deltaX, deltaY; // Mozgat�shoz delta �rt�kek
    bool isDragging; // Mozgat�s �llapota

public:

    //Konstruktor
    SpinBox(int x, int y, int w, int h, string windowTitle, int minValue, int maxValue);

    //Rajzol�
    virtual void Draw();

    int setValue(int newValue);

    //Event Handler
    virtual void EventHandler(int mouseX, int mouseY, event ev);

    virtual string GetValue();
};

#endif // SPINBOX_HPP
