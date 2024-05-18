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

const int XX = 1800;
const int YY = 1000;

class Cell : public Widget {
    int state; // 0 - üres, 1 - X, 2 - O

public:
    Cell(int x, int y, int w, int h) : Widget(x, y, w, h), state(0) {}

    void Draw() {
        gout << move_to(x+w/14, y+w/14) << color(31, 54, 65) << box(w - w/7, h - w/7);

        //Érték
        if (state == 1) {
            //X
            int margin = w / 5;
            int thickness = w / 5;

            gout << color(157, 204, 210);

            for (int i = 0; i < thickness; ++i) {
                gout << move_to(x + i + margin, y + margin) << line_to(x + w - thickness - margin + i, y + h - margin);
                gout << move_to(x + i + margin, y + h - margin) << line_to(x + w - thickness - margin + i, y + margin);
            }

        } else if (state == 2) {
            //O
            int margin = w / 5;
            int radius = (w - 2 * margin) / 2;
            int centerX = x + w / 2;
            int centerY = y + h / 2;
            int thickness = w / 8;

            for (int i = 0; i < thickness; ++i) {
                for (double j = 0; j <= 360; j += 0.2) {
                    double angle = j * M_PI / 180;
                    int endX = centerX + (radius - i) * cos(angle);
                    int endY = centerY + (radius - i) * sin(angle);
                    gout << move_to(endX, endY) << color(255, 135, 85) << dot;
                }
            }
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

bool resetCallback() {
    return true;
}

class TicTacToe : public Widget {
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
    TicTacToe(int x, int y, int w, int h, int boardSize) : Widget(x,y,w,h) , boardSize(boardSize), cellSize(YY/boardSize), currentPlayer('X'), winnerPlayer(0),
    won(false), full(false), winX(0), winO(0), Selector(new SpinBox(100,150,250,150, 15, 30)), inGame(false) {
        for (int i = 0; i < boardSize; ++i) {
            vector<Cell> row;
            for (int j = 0; j < boardSize; ++j) {
                row.emplace_back(x + i * cellSize, j * cellSize, cellSize, cellSize);
            }
            board.push_back(row);
        }
    }

    void Draw() {
        //bgcolor
        gout << move_to(0,0) << color(26,42,51) << box(XX,YY);
        if (inGame) {

            //cellák
            for (auto& row : board) {
                for (auto& cell : row) {
                    cell.Draw();
                }
            }

            //Szöveg
            gout << font("LiberationSans-Regular.ttf",50, true);
            gout << move_to(50,50) << color(230,239,246) << text("TIC TAC TOE");
            gout << font("LiberationSans-Regular.ttf",20, true);
            gout << move_to(50,100) << color(230,239,246) << text("Fully modular!");
            gout << move_to(20,YY-50) << color(230,239,246) << text("@2024 perpa4");

            //Indikátorok
            gout << font("LiberationSans-Regular.ttf",30, true);
            gout << move_to(XX - 300,420) << color(157, 204, 210) << box(200,100);
            gout << move_to(XX - 260,430) << color(26,42,51) << text("Player O");
            gout << move_to(XX - 210,470) << color(26,42,51) << text(to_string(winO));

            gout << move_to(XX - 300,620) << color(255, 135, 85) << box(200,100);
            gout << move_to(XX - 260,630) << color(26,42,51) << text("Player X");
            gout << move_to(XX - 210,670) << color(26,42,51) << text(to_string(winX));

            //Jelenlegi játékos, TIE, Nyertes
            gout << font("LiberationSans-Regular.ttf",40, true);
            gout << move_to(100,YY/2) << color(31, 54, 65) << box(200,100);

            if (full) gout << move_to(200 - gout.twidth("TIE")/2,YY/2 + gout.cascent()/1.3) << color(230,239,246) << text("TIE");
            else if (won) {
                gout << move_to(200 - gout.twidth("X WON")/2,YY/2 + gout.cascent()/1.3) << color(230,239,246) << text(winnerPlayer) << text(" WON");
                //Reset
                gout << font("LiberationSans-Regular.ttf",33, true);
                gout << move_to(25,YY/2+150) << color(31, 54, 65) << box(350,100);
                gout << move_to(200 - gout.twidth("[SPACE] for rematch!")/2,YY/2 + 150 + gout.cascent()) << color(230,239,246) << text("[SPACE] for rematch!");
            }
            else {
                gout << move_to(123,YY/2 + gout.cascent()/1.3) << color(230,239,246) << text("TURN ") << text(currentPlayer);
                //Reset
            }
        }
        else {
            gout << move_to(XX/2-250, 0) << color(31, 54, 65) << box(500,YY);

            gout << font("LiberationSans-Regular.ttf",50, true);
            gout << move_to(XX/2 - gout.twidth("TIC TAC TOE")/2,50) << color(230,239,246) << text("TIC TAC TOE");
            gout << font("LiberationSans-Regular.ttf",20, true);
            gout << move_to(XX/2 - gout.twidth("Fully modular!")/2,100) << color(230,239,246) << text("Fully modular!");
            gout << move_to(XX/2 - gout.twidth("@2024 perpa4")/2,YY-50) << color(230,239,246) << text("@2024 perpa4");
            Selector->Draw();
        }
    }

    bool checkWin(int state) {
        int dx[] = {1, 0, 1, -1}; // Irányok: jobb, le, átlós jobb-le, átlós bal-le
        int dy[] = {0, 1, 1, 1};

        //Végigjárja az összes cellát
        for (size_t row = 0; row < board.size(); ++row) {
            for (size_t col = 0; col < board[0].size(); ++col) {
                //Check
                if (board[row][col].getState() == state) {
                    //Minden irányban
                    for (int i = 0; i < 4; ++i) {
                        int count = 1; //1, mivel most raktunk le egy x-et vagy egy o-t

                        //Mindkét irány
                        for (int j = -1; j <= 1; j += 2) {
                            int newRow = row + j * dx[i];
                            int newCol = col + j * dy[i];

                            while (newRow >= 0 && static_cast<size_t>(newRow) < board.size() && newCol >= 0 && static_cast<size_t>(newCol) < board[0].size() && board[newRow][newCol].getState() == state) {
                                ++count;
                                newRow += j * dx[i];
                                newCol += j * dy[i];
                            }
                        }

                        if (count >= 5) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    bool checkFull() {
        for (const auto& row : board) {
            for (const auto& cell : row) {
                if (cell.getState() == 0) {
                    return false; // Ha talált egy üreset, akkor biztos hogy nem telt meg a pálya
                }
            }
        }
        return true;
    }

    void EventHandler(int mouseX, int mouseY, event ev) {
        if (inGame) {
            if (!won && !full) {
                if (ev.type == ev_mouse && ev.button == btn_left) {
                    for (auto& row : board) {
                        for (auto& cell : row) {
                            if (cell.isHover(ev.pos_x, ev.pos_y) && cell.getState() == 0) {
                                cell.setState(currentPlayer == 'X' ? 1 : 2);

                                if (checkWin(cell.getState())) {
                                    cout << currentPlayer << " has won the game!";
                                    if (currentPlayer == 'X') {
                                            winX++;
                                            winnerPlayer = 'X';
                                    }
                                    if (currentPlayer == 'O') {
                                            winO++;
                                            winnerPlayer = 'O';
                                    }
                                    won = true; //Nyert, szóval blokkoljon további interakciót
                                }

                                if (checkFull()) {
                                    cout << "Tie!";
                                    full = true;
                                }

                                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                                return;
                            }
                        }
                    }
                }
            }
            else {
                if (ev.keycode == key_space) Restart();
            }
        }
        else {
            Selector->EventHandler(mouseX, mouseY, ev);
        }
    }

    void Restart() {
        //Végigjárja az összes cellát
        for (size_t row = 0; row < board.size(); ++row) {
            for (size_t col = 0; col < board[0].size(); ++col) {
                board[row][col].setState(0);
                full = false;
                won = false;
            }
        }
    }
};


int main()
{
    gout.open(XX, YY);

    Widget* T = new TicTacToe(XX/2 - YY/2,0,0,0,20);

    gout << refresh;
    event ev;
    while (gin >> ev && ev.keycode != key_escape) {

        T->Draw();
        T->EventHandler(ev.pos_x, ev.pos_y, ev);

        gout << refresh;
    }

    return 0;
}
