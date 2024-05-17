#include "graphics.hpp"
#include "vector"
#include "iostream"
#include "fstream"

#include "Widget.hpp"
#include "SpinBox.hpp"
#include "ListBox.hpp"
#include "Button.hpp"

using namespace genv;
using namespace std;

const int XX = 800;
const int YY = 800;

void PrintButton(int mouseX, int mouseY, event ev, vector<Widget*> w) {
    gout << font("LiberationSans-Regular.ttf",20);
    //Háttérszín
    gout << move_to(0,0) << color(51,102,153) << box(XX,YY);

    //Szöveg
    gout << move_to(20,20) << color(255,255,255) << text("A Widgetek mozgathaóak, a ListBox görgethető.");
    gout << move_to(20,40) << color(255,255,255) << text("Nagyjából C# Forms-os kinézet, de van benne régebbi Windows design is.");
    gout << move_to(20,60) << color(255,255,255) << text("Gombnyomásra [Nyilak] [Pg] növelhető és csökkenthető a SpinBoxok értéke.");

    ofstream file;

    bool isPressedPrint = false;

    int buttonX = 300;
    int buttonY = 650;

    int buttonWidth = 200;
    int buttonHeight = 50;

    gout << move_to(buttonX, buttonY) << color(105, 105, 105) << box(buttonWidth, buttonHeight)
         << move_to(buttonX, buttonY) << color(255, 255, 255) << box(buttonWidth - 2, buttonHeight - 2);
    if (isPressedPrint) gout <<  move_to(buttonX + 2, buttonY + 2) << color(200, 200, 200) << box(buttonWidth - 4, buttonHeight - 4);
    else gout <<  move_to(buttonX + 2, buttonY + 2) << color(240, 240, 240) << box(buttonWidth - 4, buttonHeight - 4);

    gout << font("LiberationSans-Regular.ttf",30) << move_to(buttonX + buttonWidth/2 - gout.twidth("Print")/2, buttonY + buttonHeight/2 - 19) << color(0, 0, 0) << text("Print");

    if (ev.button == btn_left) {
        if (mouseX > buttonX &&
            mouseX < buttonX + buttonWidth &&
            mouseY > buttonY &&
            mouseY < buttonY + buttonHeight)
        {
            isPressedPrint = true;
            cout << "Print" << endl;;

            file.open ("output.txt");
            if (!file) {
                cout << "File could not be created!";
            }
            else {
                cout << "File created successfully!";
                //Kiíratása minden tömb elem értékének
                for (auto x : w) {
                    file << x->GetValue() << " ";
                }
            }
        }
    }
    if (ev.button == -btn_left) {
        isPressedPrint = false;
    }

    file.close();
}

int main()
{
    gout.open(XX, YY);

    //Widget tömb és elemei
    vector<Widget*> w;
    Widget * sBox = new SpinBox(100,150,250,150,"C++ SpinBox", 0, 20);
    w.push_back(sBox);

    //Widget * sBox2 = new SpinBox(100,400,250,150,"C++ SpinBox", -10, 10);
    //w.push_back(sBox2);

    Widget * lBox = new ListBox(500,150,250,175, "Hét Napjai Románul", {"Luni", "Marti", "Miercuri", "Joi", "Vineri", "Sambata", "Duminica"});
    w.push_back(lBox);

    //Widget * lBox2 = new ListBox(500,400,250,175, "Hónapok Románul", {"Ianuarie", "Februarie", "Martie", "Aprilie", "Mai", "Iunie", "Iulie", "August", "Septembrie", "Octombrie", "Noiembrie", "Decembrie"});
    //w.push_back(lBox2);

    Widget * Btn1 = new Button(500,400,200,50, "", 35, "Klikk");

    gout << refresh;
    event ev;
    while (gin >> ev && ev.keycode != key_escape) {
        PrintButton(ev.pos_x, ev.pos_y, ev, w);

        for (auto x : w) {
            x->EventHandler(ev.pos_x, ev.pos_y, ev);
            x->Draw();
        }

        Btn1->EventHandler(ev.pos_x, ev.pos_y, ev);
        Btn1->Draw();
        gout << refresh;
    }

    return 0;
}
