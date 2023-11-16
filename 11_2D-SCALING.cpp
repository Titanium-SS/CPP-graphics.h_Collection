/*
The following code implements 2D transformation called SCALING on a triangle.
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

// Function to perform scaling
pair<int, int> scale(int x, int y, int xc, int yc, float sx, float sy) {
    float originalMatrix[3] = {x - xc, y - yc, 1};

    float scalingMatrix[3][3] = {{sx,  0, 0},
                                 { 0, sy, 0},
                                 { 0,  0, 1}};

    float resultMatrix[3] = {0};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            resultMatrix[i] += scalingMatrix[i][j] * originalMatrix[j];
        }
    }

    // Scaled point = original point + scaling factor
    int scaledX = xc + resultMatrix[0];
    int scaledY = yc + resultMatrix[1];

    putpixel(scaledX, scaledY, WHITE);

    return make_pair(scaledX, scaledY);
}

int main(int argc, char* argv[]) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Define the original points of the triangle
    int x1 = 200, y1 = 350;
    int x2 = 400, y2 = 350;
    int x3 = 300, y3 = 200;

    int arr[] = {x1, y1, x2, y2, x3, y3, x1, y1};
    setcolor(RED);
    drawpoly(arr);

    // Calculate the Centroid of the triangle
    float CX = (x1 + x2 + x3) / 3.0;
    float CY = (y1 + y2 + y3) / 3.0;

    // Scaling of Points
    pair<int, int> s1, s2, s3;

    const int steps = 50; // Increase the number of steps for smoother scaling

    for (int i = 1; i <= steps; ++i) {
        cleardevice();

        setcolor(RED);
        drawpoly(arr);

        // Perform scaling with updated values
        float newSx = 1.0 + (i / 50.0); // Increase the scaling factor for a larger final size
        float newSy = 1.0 + (i / 50.0);

        s1 = scale(x1, y1, CX, CY, newSx, newSy);
        s2 = scale(x2, y2, CX, CY, newSx, newSy);
        s3 = scale(x3, y3, CX, CY, newSx, newSy);

        // Draw the scaled triangle
        setcolor(GREEN);
        int scaledArr[] = {s1.first, s1.second, s2.first, s2.second, s3.first, s3.second, s1.first, s1.second};
        drawpoly(scaledArr);

        delay(50);
    }

    cout << "+----------------------------------+\n";
    cout << "|  " << "Old Points" << setw(3) << "|" << setw(16) << "Scaled Points" << setw(4) << "|" << endl;
    cout << "+----------------------------------+\n";
    cout << "|" << setw(6) << x1 << "," << y1 << setw(5) << "|" << setw(9) << s1.first << "," << s1.second
         << setw(7) << "|" << endl;
    cout << "|" << setw(6) << x2 << "," << y2 << setw(5) << "|" << setw(9) << s2.first << "," << s2.second
         << setw(7) << "|" << endl;
    cout << "|" << setw(6) << x3 << "," << y3 << setw(5) << "|" << setw(9) << s3.first << "," << s3.second
         << setw(7) << "|" << endl;
    cout << "+----------------------------------+\n";

    getch();
    closegraph();
    return 0;
}
