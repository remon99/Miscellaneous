#include <graphics.h>
#include <stdio.h>
#include <conio.h>

void plotEllipsePoints(int x, int y) {

    putpixel(x + getmaxx() / 2, getmaxy() / 2 - y, WHITE);
    putpixel(-x + getmaxx() / 2, getmaxy() / 2 - y, WHITE);
    putpixel(x + getmaxx() / 2, getmaxy() / 2 + y, WHITE);
    putpixel(-x + getmaxx() / 2, getmaxy() / 2 + y, WHITE);
}

void drawEllipse(int a, int b) {
    int x = 0, y = b;
    float p1 = b * b - a * a * b + 0.25 * a * a;


    while (2 * b * b * x < 2 * a * a * y) {
        plotEllipsePoints(x, y);

        if (p1 < 0) {
            p1 += 2 * b * b * (2 * x + 3);
        } else {
            p1 += 2 * b * b * (2 * x + 3) + 4 * a * a * (1 - y);
            y--;
        }
        x++;
    }


    float p2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
    while (y >= 0) {
        plotEllipsePoints(x, y);

        if (p2 > 0) {
            p2 += -4 * a * a * (y - 1);
        } else {
            p2 += 2 * b * b * (2 * x + 2) - 4 * a * a * (y - 1);
            x++;
        }
        y--;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");

    setbkcolor(BLACK);
    setcolor(WHITE);

    int a = 100;
    int b = 50;

    drawEllipse(a, b);

    getch();
    closegraph();
    return 0;
}
