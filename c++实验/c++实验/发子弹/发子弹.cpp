#include <graphics.h>
#include <conio.h>
#include <time.h>
#define High 480
#define Width 640

class CBullet {
public:
    int x;
    int y;
    int speedX;
    int speedY;
    int size;
    bool active;

    void set(int hostX, int hostY, int hostRadius) {
        x = hostX;
        y = hostY;
        size = hostRadius / 2;
        speedX = rand() % 21 - 10; 
        speedY = rand() % 21 - 10;
        active = true;
    }

    void updateXY() {
        if (active) {
            x += speedX;
            y += speedY;

            if (x + size > Width || x - size < 0 || y + size > High || y - size < 0) {
                active = false;
            }
        }
    }

    bool isActive() {
        return active;
    }
};

class CCircle {
private:
    CBullet bullet; 

public:
    int x;
    int y;
    int radius;
    int speedX;
    int speedY;

    void set(int newX, int newY, int newRadius) {
        x = newX;
        y = newY;
        radius = newRadius;
        speedX = rand() % 5 -5 ; 
        speedY = rand() % 5 -5; 
        bullet.set(x, y, radius);
    }

    void update() {
        x += speedX;
        y += speedY;

 
        if (x + radius > Width || x - radius < 0) {
            speedX = -speedX;
        }
        if (y + radius > High || y - radius < 0) {
            speedY = -speedY;
        }

        bullet.updateXY();
        if (!bullet.isActive()) {
            bullet.set(x, y, radius);
        }
    }

    void draw() {
        setfillcolor(GREEN);
        solidcircle(x, y, radius);
        if (bullet.isActive()) {
            setfillcolor(BLUE);
            solidcircle(bullet.x, bullet.y, bullet.size);
        }
    }

    void erase() {
        setfillcolor(BLACK);
        solidcircle(x, y, radius);
        if (bullet.isActive()) {
            solidcircle(bullet.x, bullet.y, bullet.size);
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
    srand((unsigned int)time(0));

    CCircle circle;
    circle.set(rand() % Width, rand() % High, 20); 

    while (1) {
        circle.erase();
        circle.update();
        circle.draw();
        FlushBatchDraw();
        Sleep(3);
    }

    gameover();
    return 0;
}
