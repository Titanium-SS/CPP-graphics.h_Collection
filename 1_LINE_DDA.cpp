/*
The following code implements the Direct Differential Algorithm for Line Drawing to draw a line.
Output is based in custom "graphic.cpp" file.
*/

#include <iostream>
#include <math.h>
#include <iomanip>
#include "graphic.cpp"

using namespace std;

auto DDA(int x1, int y1, int x2, int y2, char color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float Xinc = dx / (float) steps;
    float Yinc = dy / (float) steps;
    float X = x1;
    float Y = y1;
    
    for (int i = 0; i <= steps; i++) {
        putpixel (X,Y,color);
        cout << setw(10) << int(X) << setw(15) << int(Y) << "\n"; 
        
        X += Xinc;
        Y += Yinc;
    }
}

int main(int argc, char *argv[]) {
    int gd = DETECT, gm;
    initgraph (&gd, &gm, " ");
    
    cout << setw(15) << "x coordinate" << setw(20) << "y coordinate\n";
    cout << " ----------YELLOW LINE------------- \n";
    DDA(0, 0, 10, 10, YELLOW); 
    cout << " -----------GREEN LINE------------- \n";
    DDA(12, 8, 6, 15, GREEN);

    getch();
    closegraph();
    return 0;
}
