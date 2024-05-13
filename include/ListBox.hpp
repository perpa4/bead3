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
    //Vektor �s kiv�lasztott elem
    vector<string> items;
    vector<int> itemsY;
    int selectionIndex;

    int listBoxWidth, itemHeight ,titleBarThickness, listBoxMargin; //listbox tulajdons�gai

    int buttonWidth, buttonHeight;

    int startValue, maxDisplayed;

    int scrollStep, scrollPos;

    int buttonX, buttonY;

    int deltaX, deltaY; // Mozgat�shoz delta �rt�kek

    bool isPressedUp, isPressedDown; //Megnyomva van-e
    bool isDragging; // Mozgat�s �llapota

public:

    //Konstruktor - H�t napjai rom�nul
    ListBox(int x, int y, int w, int h, string windowTitle, vector<string> items);

    //Rajzol�
    virtual void Draw();

    int setStartValue(int newStartValue);

    //Event Handler
    virtual void EventHandler(int mouseX, int mouseY, event ev);

    virtual string GetValue();
};

#endif // LISTBOX_HPP
