#ifndef LISTBOX_HPP
#define LISTBOX_HPP

#include "graphics.hpp"
#include "Widget.hpp"

#include "vector"
#include "string"

using namespace std;
using namespace genv;

class ListBox : public Widget {
protected:
    //Vektor és kiválasztott elem
    vector<string> items;
    vector<int> itemsY;
    int selectionIndex;

    int listBoxWidth, itemHeight ,titleBarThickness, listBoxMargin; //listbox tulajdonságai

    int buttonWidth, buttonHeight;

    int startValue, maxDisplayed;

    int scrollStep, scrollPos;

    int buttonX, buttonY;

    int deltaX, deltaY; // Mozgatáshoz delta értékek

    bool isPressedUp, isPressedDown; //Megnyomva van-e
    bool isDragging; // Mozgatás állapota

public:

    //Konstruktor - Hét napjai románul
    ListBox(int x, int y, int w, int h, string windowTitle, vector<string> items);

    //Rajzoló
    virtual void Draw();

    int setStartValue(int newStartValue);

    //Event Handler
    virtual void EventHandler(int mouseX, int mouseY, event ev);

    virtual string GetValue();
};

#endif // LISTBOX_HPP
