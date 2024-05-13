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
    int x, y, w, h; //Poz�ci� - M�ret
    string windowTitle; //Ablak neve

public:
    //Konstruktor
    Widget(int x, int y, int w, int h, string windowTitle);

    //Destruktor
    virtual ~Widget();

    //Rajzol�
    virtual void Draw();

    //Event Handler
    virtual void EventHandler(int mouseX, int mouseY, event ev);

    //�rt�k ki�rat�shoz
    virtual string GetValue();
};

#endif // WIDGET_HPP
