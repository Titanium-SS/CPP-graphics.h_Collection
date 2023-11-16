/*
The following code implements the 4-Connected Flood Fill Algorithm to fill a polygon.
Output is based in custom "graphic.cpp" file.
*/

#include <iostream>
#include "graphic.cpp"

using namespace std;

void floodFill(int x, int y, int oldcolor, int newcolor)
{
    // Base cases
    if (getpixel(x, y) != oldcolor)
        return;

    // Replace the color at (x, y)
    putpixel(x, y, newcolor);

    floodFill(x + 1, y, oldcolor, newcolor);
    floodFill(x - 1, y, oldcolor, newcolor);
    floodFill(x, y + 1, oldcolor, newcolor);
    floodFill(x, y - 1, oldcolor, newcolor);
}

int main(int argc, char* argv[])
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    POLYGON(9, 9, 4, 1);
    BOUNDARY(9, 9, 9, 1);

    // Call flood fill
    floodFill(9, 9, 0 , 10);

    getch();
    closegraph();
    
    return 0;
}
