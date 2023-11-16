/*
The following code implements 2D transformation called TRANSFORMATION on a triangle.
Output is based in custom "graphics.h" library.
*/

#include <iostream>
#include <iomanip>
#include <graphics.h>

using namespace std;

void drawTriangle(int arr[]) {
    drawpoly(4, arr);
}

// Function to perform translation
pair<int, int> translate(int x, int y, int tx, int ty) {
    float originalMatrix[3] = {x, y, 1};
    float translationMatrix[3] = {tx, ty, 0};
    float resultMatrix[3] = {0};

    for (int i = 0; i < 3; i++) {
        resultMatrix[i] = originalMatrix[i] + translationMatrix[i];
    }

    // Translated point = original point + translation factor
    int translatedX = resultMatrix[0];
    int translatedY = resultMatrix[1];

    return make_pair(translatedX, translatedY);
}

int main(int argc, char* argv[]) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int x1 = 200, y1 = 350;
    int x2 = 400, y2 = 350;
    int x3 = 300, y3 = 200;

    int arr[] = {x1, y1, x2, y2, x3, y3, x1, y1};

    setcolor(RED);
    drawTriangle(arr); // Original Triangle

    int tx = 200;
    int ty = 100;

    // Translation of Points
    pair<int, int> t1 = translate(x1, y1, tx, ty);
    pair<int, int> t2 = translate(x2, y2, tx, ty);
    pair<int, int> t3 = translate(x3, y3, tx, ty);

    int translatedArr[] = {t1.first, t1.second, t2.first, t2.second, t3.first, t3.second, t1.first, t1.second};

    const int steps = 50;

    for (int i = 1; i <= steps; ++i) {
        cleardevice();

        setcolor(RED);
        drawTriangle(arr);

        // Perform translation with updated values
        int newTx = tx * i / steps;
        int newTy = ty * i / steps;

        pair<int, int> t1 = translate(arr[0], arr[1], newTx, newTy);
        pair<int, int> t2 = translate(arr[2], arr[3], newTx, newTy);
        pair<int, int> t3 = translate(arr[4], arr[5], newTx, newTy);

        int newTranslatedArr[] = {t1.first, t1.second, t2.first, t2.second, t3.first, t3.second, t1.first, t1.second};

        // Draw the translated triangle
        setcolor(GREEN);
        drawTriangle(newTranslatedArr);

        delay(50);
    }

    cout << "+----------------------------------+\n";
    cout << "|  " << "Old Points" << setw(4) << "| " << "Translated Points" << setw(2) << "|" << endl;
    cout << "+----------------------------------+\n";
    cout << "|" << setw(6) << x1 << "," << y1 << setw(5) << "|" << setw(9) << t1.first << "," << t1.second
         << setw(7) << "|" << endl;
    cout << "|" << setw(6) << x2 << "," << y2 << setw(5) << "|" << setw(9) << t2.first << "," << t2.second
         << setw(7) << "|" << endl;
    cout << "|" << setw(6) << x3 << "," << y3 << setw(5) << "|" << setw(9) << t3.first << "," << t3.second
         << setw(7) << "|" << endl;
    cout << "+----------------------------------+\n";

    getch();
    closegraph();
    return 0;
}
