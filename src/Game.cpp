#include "Game.hpp"

using namespace std;
using namespace genv;

Game::Game() {
    gout.open(XX, YY);
    ticTacToe = new TicTacToe();
}

Game::~Game() {
    delete ticTacToe;
}

void Game::run() {
    while (gin >> ev && ev.keycode != key_escape) {
        ticTacToe->Draw();
        ticTacToe->EventHandler(ev.pos_x, ev.pos_y, ev);
        gout << refresh;
    }
}
