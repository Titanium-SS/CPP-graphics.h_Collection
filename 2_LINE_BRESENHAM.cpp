/*
The following code implements the Bresenham's Line Drawing Algorithm to draw a line.
Output is based in custom "graphic.cpp" file.
*/

#include <iostream>
#include <math.h>
#include <iomanip>
#include "graphic.cpp"

using namespace std;

auto bresenham(int x1, int y1, int x2, int y2, char color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        putpixel(x1, y1, color);
        cout << setw(10) << x1 << setw(15) << y1 << "\n"; 
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}


int main(int argc, char *argv[]) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, " ");

    cout << setw(15) << "x coordinate" << setw(20) << "y coordinate\n";
    cout << " ------------CYAN LINE--------------- \n";
    bresenham(2, 3, 15, 14, CYAN); 
    cout << " ----------MAGENTA LINE-------------- \n";
    bresenham(3, 15, 8, 9, MAGENTA);

    getch();
    closegraph();
    return 0;
}
