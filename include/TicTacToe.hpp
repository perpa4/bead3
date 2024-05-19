#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include "graphics.hpp"
#include "vector"
#include "iostream"
#include "math.h"

#include "Widget.hpp"
#include "SpinBox.hpp"
#include "Button.hpp"
#include "Cell.hpp"

using namespace std;
using namespace genv;

const int XX = 1800;
const int YY = 1000;

class TicTacToe : public Widget {
protected:
    vector<vector<Cell>> board;

    int x; // x pozicio

    int boardSize;
    int cellSize;

    char currentPlayer;
    char winnerPlayer;

    bool won;
    bool full;

    int winX;
    int winO;

    Widget*Selector;

    bool inGame;

public:
    TicTacToe();

    void Initialize();

    void Draw();

    bool checkWin(int state);

    bool checkFull();

    void EventHandler(int mouseX, int mouseY, event ev);

    void Restart();

    int setBoardSize(int newSize);
};


#endif // TICTACTOE_HPP
