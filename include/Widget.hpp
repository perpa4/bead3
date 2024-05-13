#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics.hpp"
#include "Widget.hpp"

#include "vector"
#include "string"

using namespace std;
using namespace genv;

class Widget {
protected:
    int x, y, w, h; //Pozíció - Méret
    string windowTitle; //Ablak neve

public:
    //Konstruktor
    Widget(int x, int y, int w, int h, string windowTitle);

    //Destruktor
    virtual ~Widget();

    //Rajzoló
    virtual void Draw();

    //Event Handler
    virtual void EventHandler(int mouseX, int mouseY, event ev);

    //Érték kiíratáshoz
    virtual string GetValue();
};

#endif // WIDGET_HPP
