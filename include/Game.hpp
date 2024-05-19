#ifndef GAME_HPP
#define GAME_HPP

#include "graphics.hpp"
#include "TicTacToe.hpp"

using namespace std;
using namespace genv;

class Game {
private:
    genv::event ev;
    TicTacToe* ticTacToe;

public:
    Game();
    ~Game();

    void run();
};

#endif // GAME_HPP
