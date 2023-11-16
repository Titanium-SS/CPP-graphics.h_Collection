/*
The following code implements the Midpoint Line Drawing Algorithm to draw a line.
Output is based in custom "graphic.cpp" file.
*/

#include <iostream>
#include <iomanip> 
#include "graphic.cpp"

using namespace std;

void midpoint(int x1, int y1, int x2, int y2, char color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    // Decision parameter
    int d = dy - (dx/2);
    int X = x1, Y = y1;

    putpixel(X, Y, color);
    cout << setw(10) << X << setw(15) << Y << "\n"; 
    while(X != x2 || Y != y2) {
        // calculate next point
        if(d < 0)
            d = d + dy;
        else {
            d += (dy - dx);
            Y += sy;
        }
        X += sx;

        putpixel(X, Y, color);
        cout << setw(10) << X << setw(15) << Y << "\n"; 
    }
}

int main(int argc, char *argv[]) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, " ");
    cout << setw(15) << "x coordinate" << setw(20) << "y coordinate\n";
    cout << " -----------RED LINE--------------- \n";
    midpoint(1, 2, 9, 10, RED);
    cout << " -----------BLUE LINE-------------- \n";
    midpoint(2, 9, 10, 1, BLUE);

    getch();
    closegraph();

    return 0;
}
