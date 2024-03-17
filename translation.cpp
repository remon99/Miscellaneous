#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include<math.h>

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

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    setbkcolor(WHITE);
    setcolor(BLACK);

    drawLine(100, 200, 300, 100);
    drawLine(300, 100, 500, 200);
    drawLine(500, 200, 100, 200);


    outtextxy(250,220,"After translation");

    float tx=0,ty=150;
    drawLine(100+tx, 200+ty, 300+tx, 100+ty);
    drawLine(300+tx, 100+ty, 500+tx, 200+ty);
    drawLine(500+tx, 200+ty, 100+tx, 200+ty);

    getch();
    closegraph();
    return 0;
}

