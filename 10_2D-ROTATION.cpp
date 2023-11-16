/*
The following code implements 2D transformation called ROTATION on a triangle.
Output is based in custom "graphics.h" library.
*/

#include <iostream>
#include <iomanip>
#include <math.h>
#include <graphics.h>

using namespace std;

// Function to draw a polygon (triangle in this case)
void drawpoly(int arr[]) {
    drawpoly(4, arr);
}

// Function to perform rotation
pair<int, int> rotate(int x, int y, int xc, int yc, float angle) {
    // Convert angle in degrees to radians
    angle = angle * (M_PI / 180.0);

    float originalMatrix[3] = {x - xc, y - yc, 1};

    float rotationMatrix[3][3] = {{cos(angle), -sin(angle), 0},
                                  {sin(angle), cos(angle),  0},
                                  {0,          0,           1}};

    float resultMatrix[3] = {0};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            resultMatrix[i] += rotationMatrix[i][j] * originalMatrix[j];
        }
    }

    // Rotated point = original point + rotation factor
    int rotatedX = xc + resultMatrix[0];
    int rotatedY = yc + resultMatrix[1];

    return make_pair(rotatedX, rotatedY);
}

int main(int argc, char* argv[]) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int x1 = 200, y1 = 350;
    int x2 = 400, y2 = 350;
    int x3 = 300, y3 = 200;

    int arr[] = {x1, y1, x2, y2, x3, y3, x1, y1};

    setcolor(RED);
    drawpoly(arr);

    float angle = 90; // Angle of rotation in degrees

    pair<int, int> r1, r2, r3;

    const int steps = 50;

    for (int i = 1; i <= steps; ++i) {
        cleardevice();

        setcolor(RED);
        drawpoly(arr);

        // Perform rotation with updated values
        float newAngle = angle * i / steps;
        r1 = rotate(x1, y1, x2, y2, newAngle);
        r2 = rotate(x2, y2, x2, y2, newAngle);
        r3 = rotate(x3, y3, x2, y2, newAngle);

        // Draw the rotated triangle
        setcolor(GREEN);
        int rotatedArr[] = {r1.first, r1.second, r2.first, r2.second, r3.first, r3.second, r1.first, r1.second};
        drawpoly(rotatedArr);

        delay(50);
    }

    cout << "+----------------------------------+\n";
    cout << "|  " << "Old Points" << setw(3) << "|" << setw(16) << "Rotated Points" << setw(4) << "|" << endl;
    cout << "+----------------------------------+\n";
    cout << "|" << setw(6) << x1 << "," << y1 << setw(5) << "|" << setw(9) << r1.first << "," << r1.second
         << setw(7) << "|" << endl;
    cout << "|" << setw(6) << x2 << "," << y2 << setw(5) << "|" << setw(9) << r2.first << "," << r2.second
         << setw(7) << "|" << endl;
    cout << "|" << setw(6) << x3 << "," << y3 << setw(5) << "|" << setw(9) << r3.first << "," << r3.second
         << setw(7) << "|" << endl;
    cout << "+----------------------------------+\n";

    getch();
    closegraph();
    return 0;
}
