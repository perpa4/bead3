#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "graphics.hpp"
#include "Widget.hpp"

#include "vector"
#include "string"

using namespace std;
using namespace genv;

class Button : public Widget {
protected:
    int textSize;
    string value;
    bool isPressed;

public:

    //Konstruktor
    Button(int x, int y, int w, int h, int textSize, string value);

    //Rajzoló
    virtual void Draw();

    //Event Handler
    virtual void EventHandler(int mouseX, int mouseY, event ev);

    virtual string GetValue();
};

#endif // SPINBOX_HPP
