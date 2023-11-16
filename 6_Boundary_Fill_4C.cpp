/*
The following code implements the 4-Connected Boundary Fill Algorithm to fill a polygon.
Output is based in custom "graphic.cpp" file.
*/

#include <iostream>
#include "graphic.cpp"

void boundaryFill4C(int x, int y, int fill_color,int boundary_color) {
    if(getpixel(x, y) != boundary_color && getpixel(x, y) != fill_color) {
        putpixel(x, y, fill_color);
        boundaryFill4C(x + 1, y, fill_color, boundary_color);
        boundaryFill4C(x - 1, y, fill_color, boundary_color);
        boundaryFill4C(x, y + 1, fill_color, boundary_color);
        boundaryFill4C(x, y - 1, fill_color, boundary_color);

        delay(100);
    }
}

int main(int argc, char* argv[]) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    POLYGON(9, 9, 4, 1);
    BOUNDARY(9, 9, 9, 8);

    boundaryFill4C(9, 9, 2, 1);

    delay(10);
    getch();
    closegraph();
    return 0;
}
