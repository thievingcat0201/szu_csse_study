#include <graphics.h>		
#include <conio.h>
#define High 480  // ”Œœ∑ª≠√Ê≥ﬂ¥Á
#define Width 640

#define _CRT_SECURE_NO_WARNINGS

class CCircle {
private:
    int x;  
    int y;  
    int radius;  
    int vx;  
    int vy; 
public:
    CCircle(int _x, int _y, int _radius, int _vx, int _vy) : x(_x), y(_y), radius(_radius), vx(_vx), vy(_vy) {}

    void draw() {
        setfillcolor(GREEN);
        setcolor(GREEN);
        fillcircle(x, y, radius);
    }

    void erase() {
        setfillcolor(BLACK);
        setcolor(BLACK);
        fillcircle(x, y, radius);
    }

    void update() {
        x += vx;
        y += vy;


        if (x - radius <= 0 || x + radius >= Width) {
            vx = -vx;
            x += vx;
        }
        if (y - radius <= 0 || y + radius >= High) {
            vy = -vy;
            y += vy;
        }
    }
};

void updateWithoutInput(CCircle& obj) {
    obj.update();
}

void gameover() {
    EndBatchDraw();
    _getch();
    closegraph();
}

void startup() {
    initgraph(Width, High);
    BeginBatchDraw();
}

int main() {
    startup();

    CCircle cobj(Width / 2, High / 2, 30, 1, 1);

    while (1) {
        cobj.erase();
        updateWithoutInput(cobj);
        cobj.draw();
        FlushBatchDraw();
        Sleep(3);
    }

    gameover();
    return 0;
}
