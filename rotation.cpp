#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

void drawLine(int x0, int y0, int x1, int y1) {
    float x, y, dx, dy, steps;

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

void rotateAndDraw(int x0, int y0, int x1, int y1, int x2, int y2, float angle) {
    float radians = angle * (M_PI / 180.0);
    float cosA = cos(radians);
    float sinA = sin(radians);

    int x0_rotated = round(x0 * cosA - y0 * sinA);
    int y0_rotated = round(x0 * sinA + y0 * cosA);
    int x1_rotated = round(x1 * cosA - y1 * sinA);
    int y1_rotated = round(x1 * sinA + y1 * cosA);
    int x2_rotated = round(x2 * cosA - y2 * sinA);
    int y2_rotated = round(x2 * sinA + y2 * cosA);

    drawLine(x0_rotated, y0_rotated, x1_rotated, y1_rotated);
    drawLine(x1_rotated, y1_rotated, x2_rotated, y2_rotated);
    drawLine(x2_rotated, y2_rotated, x0_rotated, y0_rotated);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    setbkcolor(WHITE);
    setcolor(BLACK);

    drawLine(100, 200, 300, 100);
    drawLine(300, 100, 500, 200);
    drawLine(500, 200, 100, 200);



    float angle = 10.0;
    rotateAndDraw(100, 200, 300, 100, 500, 200, angle);



    getch();
    closegraph();
    return 0;
}
