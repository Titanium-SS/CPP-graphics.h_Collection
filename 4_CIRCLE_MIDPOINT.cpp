/*
The following code implements the Midpoint Circle Drawing Algorithm to draw a Circle.
Output is based in custom "graphic.cpp" file.
*/

#include <iostream>
#include <iomanip>
#include "graphic.cpp"

using namespace std;

void drawCircle(int xc, int yc, int x, int y, char color) {
    putpixel(xc+x, yc+y, color);
    putpixel(xc-x, yc+y, color);
    putpixel(xc+x, yc-y, color);
    putpixel(xc-x, yc-y, color);
    putpixel(xc+y, yc+x, color);
    putpixel(xc-y, yc+x, color);
    putpixel(xc+y, yc-x, color);
    putpixel(xc-y, yc-x, color);
}

void MPC(int xc, int yc, int r, char color) {
    int x = 0, y = r;
    float p = 1 - r;

    drawCircle(xc, yc, x, y, color);
    cout << setw(8) << x << setw(15) << y << setw(15) << p << endl;

    while (x < y) {
        x++;
        if (p < 0) {
            p += 2*x + 1;
        } 
        else {
            y--;
            p += 2*x - 2*y + 1;
        }   

        cout << setw(8) << x << setw(15) << y << setw(15) << p << endl;
        drawCircle(xc, yc, x, y, color);
    }
}

int main(int argc, char *argv[]) {
    int gd = DETECT, gm;
    initgraph (&gd, &gm, " ");

    cout << "x coordinate" << setw(16) << "y coordinate" << setw(25) << "decision parameter (p)" << endl;

    cout << "-----------------------TEAL CIRCLE---------------------- \n";
    MPC(7, 7, 4, TEAL);
    cout << "----------------------ORANGE CIRCLE--------------------- \n";
    MPC(7, 7, 6, ORANGE);
    getch();
    closegraph();
    return 0;
}
