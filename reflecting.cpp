#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

void drawLine(int x0, int y0, int x1, int y1) {
    float x, y, dx, dy, steps;

    // Adjust coordinates based on the center of the window
    x0 += getmaxx() / 2;
    y0 = getmaxy() / 2 - y0;  // Invert y-coordinate
    x1 += getmaxx() / 2;
    y1 = getmaxy() / 2 - y1;  // Invert y-coordinate

    dx = (float)(x1 - x0);
    dy = (float)(y1 - y0);

    if (fabs(dx) >= fabs(dy)) {
        steps = fabs(dx);
    } else {
        steps = fabs(dy);
    }

    dx = dx / steps;
    dy = dy / steps;

    x = x0;
    y = y0;

    int i = 1;
    while (i <= steps) {
        putpixel(x, y, RED);
        x += dx;
        y += dy;
        i = i + 1;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    setbkcolor(WHITE);
    setcolor(BLACK);

    drawLine(-200, -200, 0, -20);
    drawLine(0, -20, 200, -200);
    drawLine(200, -200, -200, -200);

    outtextxy(getmaxx() / 2 - 50, getmaxy() / 2 - 10, "After reflecting");

    // Reflecting the triangle in the x-axis
    drawLine(-200, 200, 0, 20);
    drawLine(0, 20, 200, 200);
    drawLine(200, 200, -200, 200);

    getch();
    closegraph();
    return 0;
}


