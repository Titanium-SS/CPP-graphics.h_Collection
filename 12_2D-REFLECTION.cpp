/*
The following code implements 2D transformation called REFLECTION on a triangle.
Output is based in custom "graphics.h" library.
*/

#include <iostream>
#include <iomanip>
#include <math.h>
#include <graphics.h>

using namespace std;

// Function to draw the triangle
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    int trianglePoints[] = {x1, y1, x2, y2, x3, y3, x1, y1};
    drawpoly(4, trianglePoints);
}

// Function to perform reflection
pair<int, int> reflect(int x, int y, float rx, float ry) {
    float originalMatrix[3] = {x, y, 1};
    float reflectionMatrix[3][3] = {{rx,  0, 0},
                                    { 0, ry, 0},
                                    { 0,  0, 1}};
    float resultMatrix[3] = {0};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            resultMatrix[i] += reflectionMatrix[i][j] * originalMatrix[j];
        }
    }

    // Reflected point
    int reflectedX = resultMatrix[0];
    int reflectedY = resultMatrix[1];

    return make_pair(reflectedX, reflectedY);
}

int main(int argc, char* argv[]) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;

    setcolor(WHITE);
    line(0, centerY, getmaxx(), centerY); // X-axis
    line(centerX, 0, centerX, getmaxy()); // Y-axis

    // Define the original points of the triangle
    int x1 = 450-centerX, y1 = 200-centerY;
    int x2 = 750-centerX, y2 = 200-centerY;
    int x3 = 600-centerX, y3 =  50-centerY;

    setcolor(RED);  // Draw the original triangle
    drawTriangle(x1+centerX, y1+centerY, x2+centerX, y2+centerY, x3+centerX, y3+centerY);

    // Shift the screen's coordinate system to ensure the origin (0, 0) is visible
    int xShift = centerX;
    int yShift = centerY;

    // Reflection of Points
    // For reflection along X-axis use rx=1 and ry=-1
    // For reflection along Y-axis use rx=-1 and ry=1
    // For reflection along origin use rx=-1 and ry=-1
    pair<int, int> r1 = reflect(x1, y1, -1, 1);
    pair<int, int> r2 = reflect(x2, y2, -1, 1);
    pair<int, int> r3 = reflect(x3, y3, -1, 1);

    setcolor(GREEN);    // Draw the reflected triangle
    drawTriangle(r1.first + xShift, r1.second + yShift, r2.first + xShift, r2.second + yShift, r3.first + xShift, r3.second + yShift);

    pair<int, int> r4 = reflect(x1, y1, 1, -1);
    pair<int, int> r5 = reflect(x2, y2, 1, -1);
    pair<int, int> r6 = reflect(x3, y3, 1, -1);

    setcolor(BLUE);     // Draw the reflected triangle
    drawTriangle(r4.first + xShift, r4.second + yShift, r5.first + xShift, r5.second + yShift, r6.first + xShift, r6.second + yShift);

    cout << "+----------------------------------+\n";
    cout << "|  " << "Old Points" << setw(3) << "|" << setw(18) << "Reflected Points" << setw(2) << "|" << endl;
    cout << "+----------------------------------+\n";
    cout << "|" << setw(6) << x1 << "," << y1 << setw(5) << "|" << setw(9) << r1.first << "," << r1.second
         << setw(7) << "|" << endl;
    cout << "|" << setw(6) << x2 << "," << y2 << setw(5) << "|" << setw(9) << r2.first << "," << r2.second
         << setw(7) << "|" << endl;
    cout << "|" << setw(6) << x3 << "," << y3 << setw(4) << "|" << setw(8) << r3.first << "," << r3.second
         << setw(7) << "|" << endl;
    cout << "+----------------------------------+\n";
    cout << "|" << setw(6) << x1 << "," << y1 << setw(5) << "|" << setw(9) << r4.first << "," << r4.second
         << setw(8) << "|" << endl;
    cout << "|" << setw(6) << x2 << "," << y2 << setw(5) << "|" << setw(9) << r5.first << "," << r5.second
         << setw(8) << "|" << endl;
    cout << "|" << setw(6) << x3 << "," << y3 << setw(4) << "|" << setw(8) << r6.first << "," << r6.second
         << setw(8) << "|" << endl;
    cout << "+----------------------------------+\n";

    getch();
    closegraph();
    return 0;
}
