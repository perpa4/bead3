#include "ListBox.hpp"
#include "graphics.hpp"
#include "iostream"

#include "vector"
#include "string"

using namespace std;
using namespace genv;

const int XX = 800;
const int YY = 800;

ListBox::ListBox(int x, int y, int w, int h, string windowTitle, vector<string> items) : Widget(x, y, w, h, windowTitle),
items(items), listBoxWidth(200), itemHeight(25), listBoxMargin(25), titleBarThickness(30), isPressedUp(false), isPressedDown(false),
maxDisplayed(5), selectionIndex(1), buttonWidth(20), buttonHeight(20), scrollStep(10), scrollPos(0), startValue(0), buttonX(x + (w / 2) + (listBoxWidth / 2) - buttonWidth), buttonY(y + listBoxMargin) {}

//Rajzoló
void ListBox::Draw() {
    gout << font("LiberationSans-Regular.ttf",15);

    //ToolBar
    gout << move_to(x, y - titleBarThickness) << color(255, 255, 255) << box(w, titleBarThickness);
    //Szöveg
    gout << move_to(x + 10, y - 25) << color(0, 0, 0) << text(windowTitle);

    //Ablak
    gout << move_to(x, y) << color(240,240,240) << box(w,h);

    //ListBox
    gout << move_to(x + (w / 2) - (listBoxWidth / 2), y + listBoxMargin) << color(160, 160, 160) << box(listBoxWidth - buttonWidth, itemHeight * maxDisplayed)
         << move_to(x + (w / 2) + 2 - (listBoxWidth / 2), y + listBoxMargin + 2) << color(255, 255, 255) << box(listBoxWidth - buttonWidth, itemHeight * maxDisplayed);

    //Scrollbar
    //gout << move_to(x + (w / 2) + (listBoxWidth / 2) - buttonWidth, y + listBoxMargin) << color(240, 240, 240) << box(buttonWidth, itemHeight * maxDisplayed);

    if (items.size() > maxDisplayed) {
        //Fel
        gout << move_to(buttonX, buttonY) << color(105, 105, 105) << box(buttonWidth, buttonHeight)
             << move_to(buttonX, buttonY) << color(255, 255, 255) << box(buttonWidth - 2, buttonHeight - 2);
        if (isPressedUp) gout <<  move_to(buttonX + 2, buttonY + 2) << color(200, 200, 200) << box(buttonWidth - 4, buttonHeight - 4);
        else gout <<  move_to(buttonX + 2, buttonY + 2) << color(240, 240, 240) << box(buttonWidth - 4, buttonHeight - 4);

        //Szöveg
        gout << move_to(buttonX + 2, buttonY) << color(0, 0, 0) << text("▲");

        //Le
        gout << move_to(buttonX, buttonY + (itemHeight * maxDisplayed) - buttonHeight) << color(105, 105, 105) << box(buttonWidth, buttonHeight)
             << move_to(buttonX, buttonY + (itemHeight * maxDisplayed) - buttonHeight) << color(255, 255, 255) << box(buttonWidth - 2, buttonHeight - 2);
        if (isPressedDown) gout <<  move_to(buttonX + 2, buttonY + 2 + (itemHeight * maxDisplayed) - buttonHeight) << color(200, 200, 200) << box(buttonWidth - 4, buttonHeight - 4);
        else gout <<  move_to(buttonX + 2, buttonY + 2 + (itemHeight * maxDisplayed) - buttonHeight) << color(240, 240, 240) << box(buttonWidth - 4, buttonHeight - 4);

        //Szöveg
        gout << move_to(buttonX + 2, buttonY + (itemHeight * maxDisplayed) - buttonHeight) << color(0, 0, 0) << text("▼");
    }

    //Érték

    gout << move_to(x, y + listBoxMargin);
    for (int i = startValue; i < startValue+maxDisplayed; i++) {

        itemsY.push_back(y + listBoxMargin + (i-startValue)*itemHeight + 2);

        if (i == selectionIndex) gout << move_to(x + (w / 2) - (listBoxWidth / 2) + 2, y + listBoxMargin + (i-startValue)*itemHeight + 2) << color(50,155,255) << box(listBoxWidth - 2 - buttonWidth, itemHeight);
        else if (i % 2 == 0) gout << move_to(x + (w / 2) - (listBoxWidth / 2) + 2, y + listBoxMargin + (i-startValue)*itemHeight + 2) << color(239,238,255) << box(listBoxWidth - 2 - buttonWidth, itemHeight);
        else if (i % 2 != 0) gout << move_to(x + (w / 2) - (listBoxWidth / 2) + 2, y + listBoxMargin + (i-startValue)*itemHeight + 2) << color(255,255,255) << box(listBoxWidth - 2 - buttonWidth, itemHeight);

        if (i < items.size()) {
            gout << move_to(x + (w / 2) - (listBoxWidth / 2) + 10, y + listBoxMargin + ((i-startValue) * itemHeight)) << font("LiberationSans-Regular.ttf",20);
            if (i == selectionIndex) gout << color(255,255,255) << text(items[i]);
            else gout << color(0,0,0) << text(items[i]);
        }
    }
}

int ListBox::setStartValue(int newStartValue) {
    startValue = newStartValue;
}

//Event Handler
void ListBox::EventHandler(int mouseX, int mouseY, event ev) {
    //Up
    if (ev.button == btn_left) {
        if (mouseX > buttonX &&
            mouseX < buttonX + buttonWidth &&
            mouseY > buttonY &&
            mouseY < buttonY + buttonHeight)
        {
            isPressedUp = true;
            cout << "Touch" << endl;;
            if (startValue-1 >= 0) setStartValue(startValue-1);
        }

        if (mouseX > buttonX &&
            mouseX < buttonX + buttonWidth &&
            mouseY > buttonY + (itemHeight * maxDisplayed) - buttonHeight &&
            mouseY < buttonY + (itemHeight * maxDisplayed))
        {
            isPressedDown = true;
            cout << "Touch" << endl;;
            if (startValue+maxDisplayed < items.size()) setStartValue(startValue+1);
        }
    }

    //Görgetés
    if (mouseX > x + (w / 2) - (listBoxWidth / 2) && mouseX < x + (w / 2) + (listBoxWidth / 2) - buttonWidth && mouseY > y && mouseY < y + h) {
        if (ev.button == btn_wheelup)
        {
            cout << "Wheelup" << endl;;
            if (startValue-1 >= 0) setStartValue(startValue-1);
        }
        if (ev.button == btn_wheeldown)
        {
            cout << "Wheeldown" << endl;;
            if (startValue+maxDisplayed < items.size()) setStartValue(startValue+1);
        }
    }


    if (ev.button == -btn_left) {
        isPressedUp = false;
        isPressedDown = false;
    }

    //Kijelölés
    if (mouseX > x + (w / 2) - (listBoxWidth / 2) && mouseX < x + (w / 2) + (listBoxWidth / 2) - buttonWidth && mouseY > y && mouseY < y + h) {
        for (size_t i = 0; i < itemsY.size(); ++i) {
            if (mouseY >= itemsY[i] && mouseY < itemsY[i] + itemHeight) {
                if (ev.button == btn_left)
                selectionIndex = startValue+i;
                break;
            }
        }
    }
}
string ListBox::GetValue() {
    return items[selectionIndex];
};
