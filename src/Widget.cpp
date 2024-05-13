#include "Widget.hpp"

#include "vector"
#include "string"

using namespace std;

Widget::Widget(int x, int y, int w, int h, string windowTitle) : x(x), y(y), w(w), h(h), windowTitle(windowTitle) {}
/**<  */
//Destruktor
Widget::~Widget() {}

//Rajzoló
void Widget::Draw() {};

//Event Handler
void Widget::EventHandler(int mouseX, int mouseY, event ev) {};

//Kiíratáshoz
string Widget::GetValue() {};
