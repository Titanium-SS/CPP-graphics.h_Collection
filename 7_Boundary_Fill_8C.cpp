/*
The following code implements the 8-Connected Boundary Fill Algorithm to fill a polygon.
Output is based in custom "graphic.cpp" file.
*/

#include <iostream>
#include "graphic.cpp"

void boundaryFill8C(int x, int y, int fill_color,int boundary_color) {
    if(getpixel(x, y) != boundary_color && getpixel(x, y) != fill_color) {
        putpixel(x, y, fill_color);
        boundaryFill8C(x+1, y, fill_color, boundary_color);
        boundaryFill8C(x-1, y, fill_color, boundary_color);
        boundaryFill8C(x,   y+1, fill_color, boundary_color);
        boundaryFill8C(x,   y-1, fill_color, boundary_color);
        boundaryFill8C(x+1, y+1, fill_color, boundary_color);
        boundaryFill8C(x-1, y-1, fill_color, boundary_color);
        boundaryFill8C(x+1, y-1, fill_color, boundary_color);
        boundaryFill8C(x-1, y+1, fill_color, boundary_color);
        
        delay(20);
        
    }
}

int main(int argc, char* argv[]) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    POLYGON(9, 9, 4, 1);
    BOUNDARY(9, 9, 9, 1);

    boundaryFill8C(9, 9, 2, 1);


    getch();
    closegraph();
    return 0;
}
