#include "graphics.hpp"
#include "vector"
#include "iostream"
#include "fstream"
#include "math.h"

#include "Widget.hpp"
#include "SpinBox.hpp"
#include "Button.hpp"

using namespace genv;
using namespace std;

const int XX = 1920;
const int YY = 1080;

class Cell : public Widget {
    bool isPressed;
    int state; // 0 - üres, 1 - X, 2 - O

public:
    Cell(int x, int y, int w, int h) : Widget(x, y, w, h), state(0), isPressed(false) {}

    void Draw() {
        gout << move_to(x+w/14, y+w/14) << color(255, 255, 255) << box(w - w/7, h - w/7);

        //Érték
        if (state == 1) {
            //X
            int margin = w / 5;
            int thickness = w / 7;

            for (double i = 0; i < thickness; i+=0.5) {
                gout << color(24, 188, 156);

                gout << move_to(x + margin - i + (thickness / 2), y + margin + i - (thickness / 2))
                     << line(w - margin * 2, h - margin * 2);

                gout << move_to(x + margin - i + (thickness / 2), y + margin + i - (thickness / 2))
                     << line(w - margin * 2, h - margin * 2);
            }

        } else if (state == 2) {
            //O
            int margin = w / 5;
            int radius = (w - 2 * margin) / 2;
            int centerX = x + w / 2;
            int centerY = y + h / 2;
            int thickness = w / 8;

            for (int i = 0; i < thickness; ++i) {
                for (int j = 0; j <= 360; j += 1) {
                    double angle = j * M_PI / 180;
                    int endX = centerX + (radius - i) * cos(angle);
                    int endY = centerY + (radius - i) * sin(angle);
                    gout << move_to(endX, endY) << color(44, 62, 80) << dot;
                }
            }
        }
    }

    void EventHandler(event ev, int mouseX, int mouseY) {
        if (ev.button == btn_left) {
            if (mouseX > x &&
                mouseX < x + w &&
                mouseY > y &&
                mouseY < y + h)
            {
                isPressed = true;
            }
        }
        if (ev.button == -btn_left) {
            isPressed = false;
        }
    }

    int getState() const {
        return state;
    }

    void setState(int newState) {
        state = newState;
    }

    bool isHover(int mouse_x, int mouse_y) {
        return mouse_x >= x && mouse_x <= x + w && mouse_y >= y && mouse_y <= y + h;
    }
};

class TicTacToe {
    vector<vector<Cell>> board;
    int boardSize;
    int cellSize;
    char currentPlayer;

public:
    TicTacToe(int size) : boardSize(size), currentPlayer('X'), cellSize(YY/boardSize) {
        for (int i = 0; i < size; ++i) {
            vector<Cell> row;
            for (int j = 0; j < size; ++j) {
                row.emplace_back(i * cellSize, j * cellSize, cellSize, cellSize);
            }
            board.push_back(row);
        }
    }

    void Draw() {
        //bgcolor
        gout << move_to(0,0) << color(172,244,230) << box(XX,YY);

        for (auto& row : board) {
            for (auto& cell : row) {
                cell.Draw();
            }
        }
    }

    void EventHandler(event ev, int mouseX, int mouseY) {
        if (ev.type == ev_mouse && ev.button == btn_left) {
            for (auto& row : board) {
                for (auto& cell : row) {
                    if (cell.isHover(ev.pos_x, ev.pos_y) && cell.getState() == 0) {
                        cell.setState(currentPlayer == 'X' ? 1 : 2);
                        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                        return;
                    }
                }
            }
        }
    }

    bool isGameOver() {
        return false;
    }

    int getBoardSize() {
        return boardSize;
    }
};


int main()
{
    gout.open(XX, YY);

    TicTacToe* T = new TicTacToe(15);

    gout << refresh;
    event ev;
    while (gin >> ev && ev.keycode != key_escape) {

        T->Draw();
        T->EventHandler(ev, ev.pos_x, ev.pos_y);

        gout << refresh;
    }

    return 0;
}
