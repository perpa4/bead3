#include "Widget.hpp"

#include "vector"
#include "string"

using namespace std;

Widget::Widget(int x, int y, int w, int h, string windowTitle) : x(x), y(y), w(w), h(h), windowTitle(windowTitle) {}
/**<  */
//Destruktor
Widget::~Widget() {}

//Rajzol�
void Widget::Draw() {};

//Event Handler
void Widget::EventHandler(int mouseX, int mouseY, event ev) {};

//Ki�rat�shoz
string Widget::GetValue() {};
