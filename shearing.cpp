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

    drawLine(10, 20, 30, 10);
    drawLine(30, 10, 50, 20);
    drawLine(50, 20, 10, 20);


    outtextxy(250,220,"After shearing");

    float sx=2.3;
    drawLine(10+sx*20, 20, 30+sx*10, 10);
    drawLine(30+sx*10, 10, 50+sx*20, 20);
    drawLine(50+sx*20, 20, 10+sx*20, 20);

    getch();
    closegraph();
    return 0;
}


