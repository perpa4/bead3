#include "graphics.hpp"
#include "vector"
#include "iostream"
#include "fstream"

#include "Widget.hpp"
#include "SpinBox.hpp"
#include "ListBox.hpp"

using namespace genv;
using namespace std;

const int XX = 800;
const int YY = 800;

int main()
{
    gout.open(XX, YY);

    gout << refresh;
    event ev;
    while (gin >> ev && ev.keycode != key_escape) {



        gout << refresh;
    }
    return 0;
}
