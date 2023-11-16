/*
The following code implements the Midpoint Ellipse Drawing Algorithm to draw an Ellipse.
Output is based in custom "graphic.cpp" file.
*/

#include <iostream>
#include <iomanip>
#include "graphic.cpp"

using namespace std;

void drawEllipse(int xc, int yc, int x, int y, char color) {
    putpixel(xc+x, yc+y, color);
    putpixel(xc-x, yc+y, color);
    putpixel(xc+x, yc-y, color);
    putpixel(xc-x, yc-y, color);
}

void MPE(int xc, int yc, int a, int b, char color) {
    float dx = (float)(a * a) / sqrt(a * a + b * b);
    float dy = (float)(b * b) / sqrt(a * a + b * b);
    float d1 = b*b - a*a*b + 0.25*a*a;
    int x = 0;
    int y = b;


    putpixel(xc+x, yc+y, color);
    cout << setw(5) << "-- INTIAL POINT --" << endl;
    cout << setw(8) << xc+x << setw(15) << yc+y << setw(18) << int(d1) << endl;
    putpixel(xc-x, yc-y, color);

    // Region 1
    cout << setw(5) << "-- REGION I --" << endl;
    while (2.0 * b * b * x <= 2.0 * a * a * y) {
        if (d1 < 0) {
            d1 += 2.0 * b * b * (x + 1);
        } else {
            d1 += 2.0 * (b * b * (x + 1) - a * a * (y - 1));
            y--;
        }
        x++;

        cout << setw(8) << x << setw(15) << y << setw(18) << int(d1) << endl;
        drawEllipse(xc, yc, x, y, color);
    }


    // Region 2
    cout << setw(5) << "-- REGION II --" << endl;
    float d2 = ((b * (x + 0.5)) * (b * (x + 0.5))) + ((a * (y - 1)) * (a * (y - 1))) - (a * a * b * b);
    while (y >= 0) {
        if (d2 < 0) {
            d2 += 2.0 * b * b * (x + 1);
            x++;
        } else {
            d2 += 2.0 * (b * b * (x + 1) - a * a * (y - 1));
            y--;
        }

        cout << setw(8) << x << setw(15) << y << setw(18) << int(d2) << endl;
        drawEllipse(xc, yc, x, y, color);
        delay(10);
    }
}

int main(int argc, char* argv[]) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, " ");

    cout << setw(8) << "x coordinate" << setw(15) << "y coordinate" << setw(20) << "decision parameter" << endl;
    MPE(7, 7, 7, 4, PURPLE);

    getch();
    closegraph();
    return 0;
}
