/*
The following code implements 2D transformation called SHEARING on a square.
Output is based in custom "graphics.h" library.
*/

#include <iostream>
#include <iomanip>
#include <graphics.h>

using namespace std;

void drawSquare(int arr[]) {
    drawpoly(5, arr);
}

// Function to perform shearing
pair<int, int> shear(int x, int y, float shearFactorX, float shearFactorY) {
    float originalMatrix[3] = {x, y, 1};
    float shearingMatrix[3][3] = {{     1,        shearFactorX, 0},
                                  {shearFactorY,        1,      0},
                                  {     0,              0,      1}};
    float resultMatrix[3] = {0};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            resultMatrix[i] += shearingMatrix[i][j] * originalMatrix[j];
        }
    }

    // Sheared point
    int shearedX = resultMatrix[0];
    int shearedY = resultMatrix[1];

    return make_pair(shearedX, shearedY);
}

int main(int argc, char* argv[]) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;

    setcolor(WHITE);
    line(0, centerY, getmaxx(), centerY); // X-axis
    line(centerX, 0, centerX, getmaxy()); // Y-axis

    // Define the original points of the square
    int x1 = 100 - centerX, y1 = 100 - centerY;
    int x2 = 300 - centerX, y2 = 100 - centerY;
    int x3 = 300 - centerX, y3 = 300 - centerY;
    int x4 = 100 - centerX, y4 = 300 - centerY;

    int initialSquare[] = {x1 + centerX, y1 + centerY, x2 + centerX, y2 + centerY, x3 + centerX, y3 + centerY, x4 + centerX, y4 + centerY, x1 + centerX, y1 + centerY};

    setcolor(RED);  // Draw the original square
    drawSquare(initialSquare);

    int xShift = centerX;
    int yShift = centerY;

    // Shearing of Points
    // For horizontal shearing, use shearFactorX != 0 and shearFactorY = 0
    // For vertical shearing, use shearFactorX = 0 and shearFactorY != 0
    float shearFactorX = 0.5;
    float shearFactorY = 0;

    const int steps = 50;

    for (int i = 1; i <= steps; ++i) {
        cleardevice();

        setcolor(WHITE);
        line(0, centerY, getmaxx(), centerY); // X-axis
        line(centerX, 0, centerX, getmaxy()); // Y-axis

        if (i == 1) {
            cout << "+-------------------------------------+\n";
            cout << "|  " << "Initial Points" << setw(3) << "|" << setw(16) << "Sheared Points" << setw(3) << "|" << endl;
            cout << "+-------------------------------------+\n";
            cout << "|" << setw(7) << x1 << "," << y1 << setw(7) << "|" << setw(8) << x1 - xShift << "," << y1 - yShift
                 << setw(6) << "|" << endl;
            cout << "|" << setw(7) << x2 << "," << y2 << setw(7) << "|" << setw(8) << x2 - xShift << "," << y2 - yShift
                 << setw(6) << "|" << endl;
            cout << "|" << setw(7) << x3 << "," << y3 << setw(10) << "|" << setw(8) << x3 << "," << y3 
                 << setw(9) << "|" << endl;
            cout << "|" << setw(7) << x4 << "," << y4 << setw(10) << "|" << setw(8) << x4 << "," << y4 
                 << setw(9) << "|" << endl;
            cout << "+-------------------------------------+\n";
        }

        // Draw the original square
        setcolor(RED);
        drawSquare(initialSquare);

        // Perform shearing with updated values
        float newShearFactorX = shearFactorX * i / steps;
        float newShearFactorY = shearFactorY * i / steps;

        pair<int, int> s1 = shear(x1, y1, newShearFactorX, newShearFactorY);
        pair<int, int> s2 = shear(x2, y2, newShearFactorX, newShearFactorY);
        pair<int, int> s3 = shear(x3, y3, newShearFactorX, newShearFactorY);
        pair<int, int> s4 = shear(x4, y4, newShearFactorX, newShearFactorY);

        int newSquare[] = {s1.first + xShift, s1.second + yShift, s2.first + xShift, s2.second + yShift,
                           s3.first + xShift, s3.second + yShift, s4.first + xShift, s4.second + yShift,
                           s1.first + xShift, s1.second + yShift};

        // Draw the sheared square
        setcolor(GREEN);
        drawSquare(newSquare);

        delay(50);
    }

    getch();
    closegraph();
    return 0;
}
