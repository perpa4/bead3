#ifndef CELL_HPP
#define CELL_HPP

#include "graphics.hpp"
#include "Widget.hpp"

#include "vector"
#include "string"

using namespace std;
using namespace genv;

class Cell : public Widget {
    int state; // 0 - üres, 1 - X, 2 - O

public:
    Cell(int x, int y, int w, int h);

    void Draw();

    int getState();

    void setState(int newState);

    bool isHover(int mouse_x, int mouse_y);
};

#endif // CELL_HPP
